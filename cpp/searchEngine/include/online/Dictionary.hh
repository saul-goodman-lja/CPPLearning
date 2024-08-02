#ifndef __DICTIONARY_HH__
#define __DICTIONARY_HH__

#include <vector>
#include <string>
#include <utility>
#include <map>
#include <set>
#include <pthread.h>

using std::vector, std::pair, std::string;
using std::set, std::map;

// 候选词推荐单例类
class Dictionary {
public:
    static Dictionary * createInstance();
    void init (); // 单例的构造函数 进行预热
    vector<pair<string, int> > & getDict(); // 获取词典
    map<string, set<int> > & getIndexTable(); // 获取索引
private:
    Dictionary();
    ~Dictionary() = default;
    Dictionary(const Dictionary &) = delete;
    Dictionary & operator=(const Dictionary &) = delete;
    static void init_r();
    static void destroy();
    static Dictionary * _instance;
    static pthread_once_t _once;
private:
    vector<pair<string, int>> _dict;
    map<string, set<int>> _index;
};
#endif