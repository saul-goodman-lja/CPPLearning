#include "../../include/online/WebPageQuery.hh"
#include "../../include/online/SplitTool.hh"
#include "../../include/online/Configuration.hh"
#include "../nlohmann/json.hpp"

#include <fstream>
#include <sstream>
#include <functional>
#include <queue>
#include <numeric>
#include <ranges>
#include <algorithm>
#include <iomanip>

using std::priority_queue;
using std::istringstream;
using std::ifstream;

WebPageQuery::WebPageQuery() = default;
WebPageQuery::~WebPageQuery() = default;
string WebPageQuery::doQuery(const string &key){
    const string &search_content = key;
    std::cout << "search_content = " << search_content << "\n";
    // 分词
    vector<string> words = SplitTool::createInstance()->cut(search_content);
    // 过滤停用词
    filterStopWords(words);
    if (words.empty())
    {  
        return "no result";
    }
    for(const string & word : words){
        std::cout << word << "\n";
    }
    // 查询倒排索引，取交集，找到网页id权重
    // 即倒排索引中，所有包含搜索词的网页id 
    unordered_map<int, vector<double>> result; // 交集结果 网页ID vector存放权重
    for(const auto &[page_id, weight] : _invertIndexLib[words[0]]){
        result[page_id].push_back(weight); // 将用户输入的第一个单词 在倒排索引表中的内容 放入交集result
    }
    for(int i = 1; i < words.size(); i++) // 遍历 用户输入单词
    {
        auto word = words[i];
        unordered_map<int, vector<double>> tmp = std::move(result); // 暂存循环过程中的交集
        result.clear();
        for(const auto &[page_id, weight] : _invertIndexLib[word]){
            if(tmp.count(page_id)){ // 在已有的交集结果中找到了，取交集
                result[page_id] = tmp[page_id]; 
                result[page_id].push_back(weight); // 向网页中添加权重
            }
        }
    }
    if(result.empty()){
        return "no result";
    }

    vector<int> pages = calculate_cosine_similarity(words, result);

    string new_ripe_page_deduplication = Configuration::getInstance().getparameter("new_ripe_page_deduplication");
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
    return jsonResp.dump();
}
vector<int> WebPageQuery::calculate_cosine_similarity(vector<string> &words, unordered_map<int, vector<double>>&weights){
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

double WebPageQuery::cosine_value(vector<double> &lhs, vector<double> &rhs){
    double lsum = sumOfSquares(lhs);
    double rsum = sumOfSquares(rhs);
    double dotProduct = std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0.0);
    return dotProduct / (sqrt(lsum) * sqrt(rsum) ); 
}

double WebPageQuery::sumOfSquares(vector<double> &obj){
    double sum = 0;
    for(auto &elem : obj){
        sum += elem;
    }
    return sum;
}

void WebPageQuery::uniformization(vector<double> &obj){
    double sum = sumOfSquares(obj);
    double _sqrt = sqrt(sum);
    for(auto & elem : obj){
        elem = elem / _sqrt;
    }
}

vector<double> WebPageQuery::generate_base_vector(vector<string> &words){
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
void WebPageQuery::filterStopWords(vector<string> &words){
    vector<string> deduplicate_words;
    for(auto &word : words){
        if(!Configuration::getInstance()._stop_words.count(word)){
            deduplicate_words.emplace_back(word);
        }
    }
    words = std::move(deduplicate_words);
}
// 使用lamada预热网页偏移库
vector<pair<int, int>> WebPageQuery::_offsetLib = []()->vector<pair<int, int>>{
    string new_offset_deduplication = Configuration::getInstance().getparameter("new_offset_deduplication");
    vector<pair<int, int>> rst;
    ifstream ifs_offset(new_offset_deduplication);
    int start, offset;
    while (ifs_offset >> start >> offset)
    {
        rst.emplace_back(start, offset);
    }
    ifs_offset.close();
    return rst;
}();

// 使用lamada预热倒排索引库
unordered_map<string, set<pair<int, double>>> WebPageQuery::_invertIndexLib = []() ->unordered_map<string, set<pair<int, double>>>{
    string invertIndex = Configuration::getInstance().getparameter("invertIndex");
    unordered_map<string, set<pair<int, double>>> rst;
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
            rst[word].insert(std::make_pair(index, weight));
        }
    }
    ifs_invertIndex.close();
    return rst;
}();