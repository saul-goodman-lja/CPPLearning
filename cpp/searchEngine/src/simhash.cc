#include <iostream>
#include <fstream>

//this define can avoid some logs which you don't need to care about.
#define LOGGER_LEVEL LL_WARN 

#include <cmath>
#include "../include/offline/Configuration.hh"
#include "simhash/Simhasher.hpp"

using namespace simhash;


class PageLibPreprocessor{
public:
    PageLibPreprocessor();
    void deduplicate();
    void simhash_process(const string &, size_t);
    void store();

private:
    void word_count();
    void process_one_page(vector<string> &words, size_t);
    void calculate_weight();
private:
    // 倒排索引
    unordered_map<string, set<pair<int, double>>> _offsetLib;
    unordered_set<string> stop_words;
 
    map<string, unordered_map<int, int>> _cnt; // 统计词频 单词在每个文档中的数量
    map<string, int> _page_nums; // 单词所在的文档数量

    // 去重
    vector<pair<size_t, size_t>> _offset; // start & size
    vector<pair<uint64_t, size_t> > _simhash; // _offset的下标
    Configuration _conf;
    static Simhasher _simhasher;
    static cppjieba::Jieba _jieba;
};
Simhasher PageLibPreprocessor::_simhasher("dict/jieba.dict.utf8", "dict/hmm_model.utf8", "dict/idf.utf8", "dict/stop_words.utf8");
cppjieba::Jieba PageLibPreprocessor::_jieba("dict/jieba.dict.utf8", "dict/hmm_model.utf8", "dict/user.dict.utf8");

// 生成倒排索引
void PageLibPreprocessor::word_count(){
    string new_ripe_page_deduplication = _conf.getparameter("new_ripe_page_deduplication");
    ifstream ifs(new_ripe_page_deduplication);
    size_t index = 0;
    for(const auto &[start, offset] : _offset){
        ifs.seekg(start);
        char *content = new char[offset + 1]();
        ifs.read(content, offset);
        string s(content);
        delete [] content;
        vector<string> words;
        _jieba.Cut(s, words, true);
        process_one_page(words, index++);
    }
}

// 统计词频 & 单词所在的文档数量
void PageLibPreprocessor::process_one_page(vector<string> &words, size_t index){
    map<string, int> tmp;
    for(const auto &word : words){
        if(stop_words.count(word)){
            continue;
        }
        tmp[word]++;
    }
    for(const auto &[word, cnt] : tmp){
        _cnt[word][index] += cnt;
        _page_nums[word]++;
    }
}

// TF / IDF
void PageLibPreprocessor::calculate_weight(){
    for(const auto &[word, page] : _cnt){
        for(const auto &[index, cnt] : page){
            double TF = cnt;
            double DF = _page_nums[word];
            double IDF = log2(1.0 * _offset.size() / (DF + 1));
            _offsetLib[word].insert(make_pair(index, TF * IDF));
        }
    }
    string invertIndex = _conf.getparameter("invertIndex");
    ofstream ofs(invertIndex);
    for(const auto &[word, page] : _offsetLib){
        ofs << word << " ";
        for(const auto &[index, weight] : page){
            ofs << index << " " << weight << " ";
        }
        ofs << "\n";
    }
    ofs.close();
    std::cout << "invertIndex已存储到 " << invertIndex << "\n";
}


// 去重
PageLibPreprocessor::PageLibPreprocessor(){
    // string new_offset = _conf.getparameter("new_offset");
    string new_offset = _conf.getparameter("new_offset_deduplication");
    ifstream ifs(new_offset);
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        size_t start = 0, offset = 0;
        iss >> start >> offset;
        _offset.push_back(make_pair(start, offset));
    }

    string word;
    string chinese_stop_words = _conf.getparameter("chinese_stop_words");
    ifstream ifs_chinest_stop_words(chinese_stop_words);
    while(ifs_chinest_stop_words >> word){
        stop_words.insert(word);
    }

    string english_stop_words = _conf.getparameter("english_stop_words");
    ifstream ifs_english_stop_words(english_stop_words);
    while(ifs_english_stop_words >> word){
        stop_words.insert(word);
    }
    ifs_chinest_stop_words.close();
    ifs.close();

    word_count();
    calculate_weight();
}

void PageLibPreprocessor::deduplicate(){

    string new_ripe_page = _conf.getparameter("new_ripe_page");
    ifstream ifs(new_ripe_page);

    size_t index = 0;
    for(const auto &[start, offset] : _offset){
        ifs.seekg(start); // 从网页偏移库读取文章
        char *content = new char[offset + 1]();
        ifs.read(content, offset);
        simhash_process(content, index++); // 处理simhash
        delete [] content; // 记得删除
    }

    ifs.close();

}
void PageLibPreprocessor::simhash_process(const string &content, size_t index){
    size_t topN = 5;
    uint64_t u = 0;
    _simhasher.make(content, topN, u);
    if(_simhash.empty()){
        _simhash.push_back(make_pair(u, index));
    }else{
        bool flag = true;
        for(const auto &elem : _simhash){
            if(Simhasher::isEqual(u, elem.first)){ // 判断simhash的值是否相等
                flag = false;
                break;
            }
        }
        if(flag){
            _simhash.push_back(make_pair(u, index));
        }
    }
}

void PageLibPreprocessor::store(){
    string new_ripe_page = _conf.getparameter("new_ripe_page");
    string new_ripe_page_deduplication = _conf.getparameter("new_ripe_page_deduplication");
    string new_offset_deduplication = _conf.getparameter("new_offset_deduplication");
    ofstream ofs_offset_deduplication(new_offset_deduplication);
    ifstream ifs_new_ripe_page(new_ripe_page);
    ofstream ofs_new_ripe_page_deduplication(new_ripe_page_deduplication);
    for(const auto &elem : _simhash){
        size_t start = _offset[elem.second].first, offset = _offset[elem.second].second;
        ofs_offset_deduplication << start << " " << offset << "\n";
        ifs_new_ripe_page.seekg(start);
        char *content = new char[offset + 1]();
        ifs_new_ripe_page.read(content, offset);
        ofs_new_ripe_page_deduplication.write(content, offset);
        delete [] content;
    }
    ofs_offset_deduplication.close();
    ofs_new_ripe_page_deduplication.close();
    ifs_new_ripe_page.close();
}
int main(int argc, char** argv)
{
    PageLibPreprocessor processer;

    // processer.deduplicate();
    // processer.store();
    // size_t topN = 5;
    // uint64_t u641 = 0, u642;

    // simhasher.make(s1, topN, u641);
    // simhasher.make(s2, topN, u642);
    
    // // cout<< bin1 << "和" << bin2 << " simhash值的相等判断如下："<<endl;
    // cout<< "海明距离阈值默认设置为3，则isEqual结果为：" << (Simhasher::isEqual(u641, u642)) << endl; 
    // cout<< "海明距离阈值默认设置为5，则isEqual结果为：" << (Simhasher::isEqual(u641, u642, 5)) << endl; 
    return 0;
}