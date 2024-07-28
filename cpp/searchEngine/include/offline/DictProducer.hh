#ifndef __DICTPRODUCER_HH__
#define __DICTPRODUCER_HH__

#include "SplitTool.hh"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

using std::string, std::vector;
using std::map, std::set;
using std::pair;

class DictProducer{
public:
    DictProducer(const string &, SplitTool *);
    ~DictProducer();
    void buildEnDict();
    void buildCnDict();
    void createIndex();
    void store(const string &filepath); //将词典写入文件
private:
    size_t nBytesCode(const char ch);
private:
    vector<string> _files; //语料库文件的绝对路径集合
    vector<pair<string, int>> _dict; //词典
    map<string, set<int>> _index; //词典索引
    SplitTool *_cuttor; //分词工具
};

#endif
