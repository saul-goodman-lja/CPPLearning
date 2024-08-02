#ifndef __WEBPAGEQUERY_HH__
#define __WEBPAGEQUERY_HH__

#include "../../include/online/SplitTool.hh"

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>

using std::set;
using std::vector, std::string, std::pair;
using std::unordered_map;

class WebPageQuery {
public:
    WebPageQuery();
    ~WebPageQuery();
    string doQuery(const string &key);
private:
    vector<int> calculate_cosine_similarity(vector<string> &, unordered_map<int, vector<double>>&); // 计算余弦相似度
    vector<double> generate_base_vector(vector<string> &); // 生成基准向量
    double sumOfSquares(vector<double> &); // 计算平方和
    void uniformization(vector<double> &); // 归一化
    double cosine_value(vector<double> &, vector<double> &);
    void filterStopWords(vector<string> &words);
private:
    static unordered_map<string, set<pair<int, double>>> _invertIndexLib;  // 倒排索引库
    static vector<pair<int, int>> _offsetLib;                              // 网页偏移库
};

#endif