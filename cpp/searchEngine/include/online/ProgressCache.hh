#ifndef __PROGRESS_CACHE_HH__
#define __PROGRESS_CACHE_HH__

#include <pthread.h>
#include <list>
#include <unordered_map>
#include <utility>
#include <string>
#include <thread>

using std::string, std::pair, std::unordered_map, std::list;


// LRU 单例 
class ProgressCache{
public:
    static ProgressCache* getInstance();
    bool isExist(const string& key);    
    string getValue(const string& key);
    void putKeyValue(const string& key, const string& value);
    std::mutex & getMutex();
private:
    ProgressCache();
    ~ProgressCache() = default;
    ProgressCache(const ProgressCache&) = delete;
    ProgressCache &operator=(const ProgressCache&) = delete;
    static void init_r();
    static void destroy();
    static ProgressCache * _instance;
    static pthread_once_t _once;
private:
    unordered_map<string, list<pair<string, string>>::iterator> _cache_map;
    list<pair<string, string>> _cache_list;
    int _capacity;
    std::mutex _mutex; // 互斥锁
};

#endif