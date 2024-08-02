#ifndef __DOUBLECACHEMANAGER_HH__
#define __DOUBLECACHEMANAGER_HH__

#include "../../include/online/LRUCache.hh"

#include <pthread.h>

#include <mutex>
#include <thread>
#include <vector>
#include <unordered_map>

using std::vector, std::unordered_map;

// 单例 缓存管理类
class DoubleCacheManager{
public:
    static DoubleCacheManager * getInstance();
    void initCache(); // 从磁盘文件中读取缓存信息
    LRUCache &getCache(const std::thread::id &); // 获取某个线程的缓存
    void periodicUpdateCaches(); // 定期更新缓存
    std::mutex& getMutex(const std::thread::id &);
private:
    vector<LRUCache> _cacheList1; // 处理用户请求
    vector<LRUCache> _cacheList2; // 合并、同步
    unordered_map<std::thread::id, size_t> _cacheMap; // 线程与缓存的映射
    vector<std::mutex> _cache_manager_mutexs; // 每个线程一把锁，缓存同步时timer管理线程占据所有锁
private:
    DoubleCacheManager();
    ~DoubleCacheManager() = default;
    DoubleCacheManager(const DoubleCacheManager &) = delete;
    DoubleCacheManager & operator=(const DoubleCacheManager &) = delete;
    static void init_r();
    static void destroy();
    static DoubleCacheManager * _instance;
    static pthread_once_t _once;
};

#endif