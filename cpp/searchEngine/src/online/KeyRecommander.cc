#include "../../include/online/KeyRecommander.hh"
#include "../../include/online/Dictionary.hh"
#include "../../include/online/TcpConnection.hh"
#include "../nlohmann/json.hpp"
#include "../../include/online/ProgressCache.hh"
#include "../../include/online/CacheManager.hh"
#include "../../include/online/DoubleCacheManager.hh"
#include "../../include/online/LogSingleTon.hh"

#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>
#include <thread>
#include <mutex>


using std::unordered_set;
using std::priority_queue;

KeyRecommander::KeyRecommander(const string& query, const TcpConnectionPtr& conn)
: _queryWord(query), _conn(conn){}

KeyRecommander::~KeyRecommander() = default;

void KeyRecommander::ProgressCache(string &result, ostringstream &oss){
    oss.str("");
    oss.clear();

    // 互斥访问，需要上锁
    std::lock_guard<std::mutex> lock(ProgressCache::getInstance()->getMutex());
    if (ProgressCache::getInstance()->isExist(_queryWord))
    {   
        result = ProgressCache::getInstance()->getValue(_queryWord);
        oss << ">>> 命中LRU Cache, 返回结果为:" << result;
        LogInfo(oss.str());
    }
    else
    {
        oss << ">>> " << _queryWord << " 未命中 LRU Cache.";
        LogInfo(oss.str());
        result = doQuery();
        ProgressCache::getInstance()->putKeyValue(_queryWord, result);
    }
}
void KeyRecommander::TimerManagerCache(string &result, ostringstream &oss){
    oss.str("");
    oss.clear();

    // timer管理线程对缓存进行同步
    // 访问前给每个线程上锁
    std::lock_guard<std::mutex> lock(CacheManager::getInstance()->getMutex(std::this_thread::get_id()));
    auto &cache = CacheManager::getInstance()->getCache(std::this_thread::get_id());
    if (cache.isExist(_queryWord))
    {   
        result = cache.getValue(_queryWord);
        oss << ">>> 命中LRU Cache, 返回结果为:" << result;
        LogInfo(oss.str());
    }
    else
    {
        oss << ">>> " << _queryWord << " 未命中 LRU Cache.";
        LogInfo(oss.str());
        result = doQuery();
        cache.addElement(_queryWord, result);
    }
}
void KeyRecommander::DoubleCache(string &result, ostringstream &oss){
    oss.str("");
    oss.clear();

    // 双缓存
    // 访问前给每个线程上锁
    std::lock_guard<std::mutex> lock(DoubleCacheManager::getInstance()->getMutex(std::this_thread::get_id()));
    auto &cache = DoubleCacheManager::getInstance()->getCache(std::this_thread::get_id());
    if (cache.isExist(_queryWord))
    {   
        result = cache.getValue(_queryWord);
        oss << ">>> 命中LRU Cache, 返回结果为:" << result;
        LogInfo(oss.str());
    }
    else
    {
        ostringstream oss;
        oss << ">>> " << _queryWord << " 未命中 LRU Cache.";
        LogInfo(oss.str());
        result = doQuery();
        cache.addElement(_queryWord, result);
    }
}

void KeyRecommander::execute(){
    string result;
    ostringstream oss;

    // 1 进程内的缓存
    // ProgressCache(result, oss);

    // 2 定时器管理缓存
    // TimerManagerCache(result, oss);

    // 3 双缓存
    DoubleCache(result, oss);

    _conn->sendInLoop(result);
}
string KeyRecommander::doQuery(){
    string search_content = _queryWord;
    std::cout << "search_content = " << search_content << "\n";
    vector<pair<string, int>> _dict = Dictionary::createInstance()->getDict();
    map<string, set<int>> _index = Dictionary::createInstance()->getIndexTable();
    unordered_set<int> index; // 用于召回，取并集
    auto cmp = [&](auto left, auto right) -> bool { // lamada表达式用来改造优先队列的比较规则
        int l_edit_distance = editDistance(_dict[left].first, search_content);
        int r_edit_distance = editDistance(_dict[right].first, search_content);
        if (l_edit_distance == r_edit_distance)
        {
            // 最小编辑距离相等则按照热度排序
            // 热度越大 优先级越高，所以是 < 
            return _dict[left] < _dict[right];
        }
        // 最小编辑距离越小 优先级越高， 所以是 > 
        return l_edit_distance > r_edit_distance;
    };

    priority_queue<int, vector<int>, decltype(cmp)> que(cmp);
    
    for (size_t idx = 0; idx != search_content.size();)
    {
        int len = nBytesCode(search_content[idx]);
        for (const auto& idx : _index[search_content.substr(idx, len)])
        {
            index.insert(idx);
        }
        idx += len;
    }

    for (const auto& idx : index)
    {
        que.emplace(idx);
    }

    vector<string> result;
    int num = 10;
    while (!que.empty() && num--)
    {
        string recommand_word = _dict[que.top()].first;
        result.push_back(recommand_word);
        que.pop();
    }

    nlohmann::json jsonArray = result;
    LogInfo(jsonArray.dump());
    return string(jsonArray.dump());
}

size_t KeyRecommander::nBytesCode(const char ch)
{
    if (ch & (1 << 7))
    {
        int nBytes = 1;
        for (int idx = 0; idx != 6; ++idx)
        {
            if (ch & (1 << (6 - idx)))
            {
                ++nBytes;
            }
            else
                break;
        }
        return nBytes;
    }
    return 1;
}
std::size_t KeyRecommander::length(const std::string& str)
{
    std::size_t ilen = 0;
    for (std::size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
int KeyRecommander::triple_min(const int& a, const int& b, const int& c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int KeyRecommander::editDistance(const string& lhs, const string& rhs)
{
    //计算最小编辑距离-包括处理中英文
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    int editDist[lhs_len + 1][rhs_len + 1];
    for (size_t idx = 0; idx <= lhs_len; ++idx)
    {
        editDist[idx][0] = idx;
    }
    for (size_t idx = 0; idx <= rhs_len; ++idx)
    {
        editDist[0][idx] = idx;
    }
    string sublhs, subrhs;
    for (size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i, ++lhs_idx)
    {
        size_t nBytes = nBytesCode(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);
        for (size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len; ++dist_j, ++rhs_idx)
        {
            nBytes = nBytesCode(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);
            if (sublhs == subrhs)
            {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j -
                                                                1];
            }
            else
            {
                editDist[dist_i][dist_j] =
                    triple_min(editDist[dist_i][dist_j - 1] + 1,
                                editDist[dist_i - 1][dist_j] + 1,
                                editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}