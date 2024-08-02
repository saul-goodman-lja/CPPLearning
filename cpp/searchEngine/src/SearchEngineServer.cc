// WaitGroup 让某个线程处于等待状态
#include <workflow/WFFacilities.h>
// WFHttpServer.h 包含server类的设计
#include "../include/offline/Configuration.hh"
#include "../nlohmann/json.hpp"
#include "simhash/Simhasher.hpp"
#include "tinyxml2.h"
#include <signal.h>
#include <workflow/WFHttpServer.h>

#include <cmath>

#include <fstream>
#include <functional>  // STL相关头文件
#include <iomanip>
#include <iostream>  // IO相关头文件
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <numeric>
#include <ranges>
#include <algorithm>

using std::ifstream, std::ofstream, std::istringstream, std::string;
using std::pair, std::unordered_set;
using std::priority_queue;
using std::vector, std::map, std::set;

class KeyRecommander
{
  public:
    KeyRecommander()
      : _server(std::bind(&KeyRecommander::process, this, std::placeholders::_1))  // 绑定this指针
    {
        worm_up();
        worm_up_page();
        ::signal(SIGINT, &KeyRecommander::signalHandler);  // static void
        if (_server.start(65535) == 0)
        {
            _waitGroup.wait();
            _server.stop();
        }
        else
        {
            ::perror("server start failed!");
        }
    }

  private:
    void worm_up_page();
    void worm_up();
    void suggest(WFHttpTask* serverTask, const string &);
    void search(WFHttpTask* serverTask, const string &);
    void default_page(WFHttpTask* serverTask);

    vector<int> calculate_cosine_similarity(vector<string> &, unordered_map<int, vector<double>>&); // 计算余弦相似度
    vector<double> generate_base_vector(vector<string> &); // 生成基准向量
    double sumOfSquares(vector<double> &); // 计算平方和
    void uniformization(vector<double> &); // 归一化
    double cosine_value(vector<double> &, vector<double> &);
    nlohmann::json xmlToJson(const std::string& xmlStr);

    void filterStopWords(vector<string> &words);
    void process(WFHttpTask* serverTask)
    {
        protocol::HttpRequest* req = serverTask->get_req();
        std::string uri = req->get_request_uri();
        std::string method = req->get_method();
        // if(method == "GET"){
        // /login?username=niqiu&password=123
        string type = uri.substr(0, uri.find('?'));
        std::cout << "type = " << type << "\n";
        std::cout << "method = " << method << "\n";
        std::cout << "uri = " << uri << "\n";
        string search_content = urlDecode(uri.substr(uri.find('=') + 1));
        if (type == "/suggest")
        {
            suggest(serverTask, search_content);
        }
        else if (type == "/search")
        {
            search(serverTask, search_content);
        }
        else
        {
            default_page(serverTask);
        }
    }
    static void signalHandler(int signum)
    {
        std::cout << "\ndone\n";
        _waitGroup.done();
    }
    size_t nBytesCode(const char ch)
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

    std::size_t length(const std::string& str)
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
    int triple_min(const int& a, const int& b, const int& c)
    {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }
    int editDistance(const string& lhs, const string& rhs)
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
        for (size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i,
                    ++lhs_idx)
        {
            size_t nBytes = nBytesCode(lhs[lhs_idx]);
            sublhs = lhs.substr(lhs_idx, nBytes);
            lhs_idx += (nBytes - 1);
            for (size_t dist_j = 1, rhs_idx = 0;
                 dist_j <= rhs_len;
                 ++dist_j, ++rhs_idx)
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
    string urlDecode(const std::string& src)
    {
        string result;
        for (size_t i = 0; i < src.length(); ++i)
        {
            if (src[i] == '%' && i + 2 < src.length())
            {
                std::string hex = src.substr(i + 1, 2);
                int value = std::stoi(hex, nullptr, 16);
                result += static_cast<char>(value);
                i += 2;  // Skip the hex part
            }
            else
            {
                result += src[i];
            }
        }
        return result;
    }

  private:
    WFHttpServer _server;
    vector<pair<string, int>> _dict;
    map<string, set<int>> _index;
    static WFFacilities::WaitGroup _waitGroup;

    Configuration _conf;
    unordered_map<string, set<pair<int, double>>> _invertIndexLib;  // 倒排索引库
    vector<pair<int, int>> _offsetLib;                              // 网页偏移库
    static cppjieba::Jieba _jieba;
};
WFFacilities::WaitGroup KeyRecommander::_waitGroup(1);
cppjieba::Jieba KeyRecommander::_jieba("dict/jieba.dict.utf8", "dict/hmm_model.utf8", "dict/user.dict.utf8");

void KeyRecommander::worm_up_page()
{
    string new_offset_deduplication = _conf.getparameter("new_offset_deduplication");
    ifstream ifs_offset(new_offset_deduplication);
    int start, offset;
    while (ifs_offset >> start >> offset)
    {
        _offsetLib.emplace_back(start, offset);
    }

    string invertIndex = _conf.getparameter("invertIndex");
    ifstream ifs_invertIndex(invertIndex);
    string line;
    while (std::getline(ifs_invertIndex, line))
    {
        istringstream iss(line);
        string word;
        int index;
        double weight;
        iss >> word;
        while (iss >> index >> weight)
        {
            _invertIndexLib[word].insert(std::make_pair(index, weight));
        }
    }
    ifs_offset.close();
    ifs_invertIndex.close();
}

void KeyRecommander::worm_up()
{
    _dict.reserve(50000);
    Configuration config;
    string dict_path = config.getparameter("dict_path");
    string dictIndex_path = config.getparameter("dictIndex_path");
    string line;
    ifstream ifs_dict(dict_path);
    while (std::getline(ifs_dict, line))
    {
        istringstream iss(line);
        string word;
        int cnt;
        while (iss >> word >> cnt)
        {
            _dict.push_back(std::make_pair(word, cnt));
        }
    }
    ifstream ifs_index(dictIndex_path);
    while (std::getline(ifs_index, line))
    {
        istringstream iss(line);
        string word;
        iss >> word;
        int index;
        while (iss >> index)
        {
            _index[word].insert(index);
        }
    }
    ifs_dict.close();
    ifs_index.close();
}

void KeyRecommander::suggest(WFHttpTask* serverTask, const string& search_content)
{
    std::cout << "search_content = " << search_content << "\n";
    unordered_set<int> index;
    auto cmp = [&](auto left, auto right) -> bool {
        int l_edit_distance = editDistance(_dict[left].first, search_content);
        int r_edit_distance = editDistance(_dict[right].first, search_content);
        if (l_edit_distance == r_edit_distance)
        {
            return _dict[left] < _dict[right];
        }
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
    std::cout << "finish index"
              << "\n";
    for (const auto& idx : index)
    {
        que.emplace(idx);
    }

    vector<string> result;
    int num = 10;
    while (!que.empty() && num--)
    {
        string recommand_word = _dict[que.top()].first;
        std::cout << recommand_word << "\n";
        result.push_back(recommand_word);
        que.pop();
    }
    // vector<string> stringArray = {"apple", "banana", "cherry"};
    nlohmann::json jsonArray = result;
    serverTask->get_resp()->append_output_body(jsonArray.dump().c_str(), jsonArray.dump().size());
    std::cout << jsonArray.dump() << "\n";
}

void KeyRecommander::search(WFHttpTask* serverTask, const string& search_content)
{
    std::cout << "search_content = " << search_content << "\n";
    vector<string> words;
    // 分词
    _jieba.Cut(search_content, words, true);
    // 过滤停用词
    filterStopWords(words);
    if (words.empty())
    {
        default_page(serverTask);
        return;
    }
    for(const string & word : words){
        std::cout << word << "\n";
    }
    // 查询倒排索引，取交集
    // 即倒排索引中，所有包含搜索词的网页id
    unordered_map<int, vector<double>> result;
    for(const auto &[page_id, weight] : _invertIndexLib[words[0]]){
        result[page_id].push_back(weight);
    }
    for(int i = 1; i < words.size(); i++)
    {
        auto word = words[i];
        unordered_map<int, vector<double>> tmp = std::move(result);
        result.clear();
        for(const auto &[page_id, weight] : _invertIndexLib[word]){
            if(tmp.count(page_id)){
                result[page_id] = tmp[page_id];
                result[page_id].push_back(weight);
            }
        }
        // result = std::move(tmp);
    }
    if(result.empty()){
        return;
    }

    vector<int> pages = calculate_cosine_similarity(words, result);

    string new_ripe_page_deduplication = _conf.getparameter("new_ripe_page_deduplication");
    ifstream ifs(new_ripe_page_deduplication);
    vector<string> pages_contents;
    for(int i : pages){
        std::cout << i << "\n";
        auto &[start, offset] = _offsetLib[i];
        ifs.seekg(start);
        char *content = new char[offset + 1]();
        ifs.read(content, offset);
        pages_contents.emplace_back(string(content));
        delete [] content;
    }
    ifs.close();

    nlohmann::json jsonResp;
    if(pages_contents.empty()){
        jsonResp = nlohmann::json::object();
    }else{
        jsonResp = pages_contents;
    }
    
    serverTask->get_resp()->append_output_body(jsonResp.dump().c_str(), jsonResp.dump().size());
    std::cout << pages_contents.size() << "------" << "\n";
    // 打印格式化的 JSON 字符串
    // std::cout << jsonResp.dump(4) << std::endl;
}

vector<int> KeyRecommander::calculate_cosine_similarity(vector<string> &words, unordered_map<int, vector<double>>&weights){
    // 生成基准向量
    vector<double> base_vector = generate_base_vector(words);
    // 归一化处理
    for(auto &[index, vec] : weights){
        uniformization(vec);
    }
    vector<int> pages;

    auto cmp = [&](auto &a, auto &b)->bool{
        return cosine_value(base_vector, weights[a]) < cosine_value(base_vector, weights[b]);
    };
    priority_queue<int, vector<int>, decltype(cmp)> que(cmp);
    for(const auto &[index, other] : weights){
        que.push(index);
    }
    int len = 5;
    while(len-- && !que.empty()){
        pages.push_back((que.top()));
        que.pop();
    }
    return pages;
}

double KeyRecommander::cosine_value(vector<double> &lhs, vector<double> &rhs){
    double lsum = sumOfSquares(lhs);
    double rsum = sumOfSquares(rhs);
    double dotProduct = std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0.0);
    return dotProduct / (sqrt(lsum) * sqrt(rsum) ); 
}

double KeyRecommander::sumOfSquares(vector<double> &obj){
    double sum = 0;
    for(auto &elem : obj){
        sum += elem;
    }
    return sum;
}

void KeyRecommander::uniformization(vector<double> &obj){
    double sum = sumOfSquares(obj);
    double _sqrt = sqrt(sum);
    for(auto & elem : obj){
        elem = elem / _sqrt;
    }
}

vector<double> KeyRecommander::generate_base_vector(vector<string> &words){
    unordered_map<string, double> weights;
    unordered_map<string, int> word_cnt;
    for(const string &word : words){
        word_cnt[word]++;
    }
    for(const auto &[word, cnt] : weights){
        double TF = cnt;
        double DF = 1;
        double IDF = log2(1.0 / (DF + 1));
        weights[word] = TF * IDF;
    }
    unordered_set<string> flag_hash;
    // TODO 返回基准向量
    vector<double> rst;
    for(const string & word : words){
        if(!flag_hash.count(word)){
            flag_hash.insert(word);
            rst.push_back(weights[word]);
        }
    }
    uniformization(rst); // 归一化
    return rst;
}

void KeyRecommander::default_page(WFHttpTask* serverTask)
{
    std::ifstream ifs("search.html");
    std::string sendBack, line;
    while (std::getline(ifs, line))
    {
        sendBack.append(line);
    }

    size_t size = sendBack.size();
    const void* body = (void*)sendBack.c_str();
    serverTask->get_resp()->append_output_body(body, size);
}

void KeyRecommander::filterStopWords(vector<string> &words)
{   
    vector<string> deduplicate_words;
    string chinese_stop_words = _conf.getparameter("chinese_stop_words");
    string english_stop_words = _conf.getparameter("english_stop_words");
    ifstream stop_cn(chinese_stop_words);
    ifstream stop_en(english_stop_words);

    unordered_set<string> stop_words;
    string word;
    while(stop_cn >> word){
        stop_words.insert(word);
    }
    while(stop_en >> word){
        stop_words.insert(word);
    }

    for(auto word : words){
        if(!stop_words.count(word)){
            deduplicate_words.push_back(word);
        }
    }

    words = std::move(deduplicate_words);

    stop_cn.close();
    stop_en.close();
}

// 将 XML 转换为 JSON
nlohmann::json KeyRecommander::xmlToJson(const std::string& xmlStr) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xmlStr.c_str());

    nlohmann::json j;

    tinyxml2::XMLElement* root = doc.RootElement();
    if (root) {
        for (tinyxml2::XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement()) {
            std::string key = element->Name();
            std::string value;
            if (element->GetText()) {
                value = element->GetText();
            }
            j[key] = value;
        }
    }

    return j;
}
int main()
{
    KeyRecommander keyRecommander;
    std::cout << "finish work.\n";
    return 0;
}