#include "../../include/online/DoubleCacheManager.hh"
#include "../../include/online/Configuration.hh"
#include "../../include/online/LogSingleTon.hh"

#include <iostream>
#include <utility> 

DoubleCacheManager * DoubleCacheManager::getInstance(){
    pthread_once(&_once,init_r);
    return _instance;
}

void DoubleCacheManager::init_r(){
    _instance = new DoubleCacheManager();
    atexit(destroy);
}

void DoubleCacheManager::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}

DoubleCacheManager::DoubleCacheManager()
: _cacheList1(stoi(Configuration::getInstance().getparameter("threadNum")))
, _cacheList2(stoi(Configuration::getInstance().getparameter("threadNum")))
, _cache_manager_mutexs(std::stoi(Configuration::getInstance().getparameter("threadNum")))
{
    initCache();
}

void DoubleCacheManager::initCache(){ // 从磁盘文件中读取缓存信息
    // 初始化CacheList1
    _cacheList1[0].readFromFile(Configuration::getInstance().getparameter("cache_path"));
    LogInfo(">>> 从磁盘读取缓存数据.");
    for(size_t idx = 1; idx < _cacheList1.size(); ++idx){
        _cacheList1[idx].update(LRUCache(_cacheList1[0]));
    }
    // 初始化CacheList2
    for(size_t idx = 0; idx < _cacheList2.size(); ++idx){
        _cacheList2[idx].update(LRUCache(_cacheList1[0]));
    }
}
LRUCache & DoubleCacheManager::getCache(const std::thread::id &tid){ // 获取某个线程的缓存
    // 如果线程Id 还未和缓存关联，则映射到缓存列表中还未分配的LRUCache
    if(!_cacheMap.count(tid)){ 
        size_t index = _cacheMap.size();
        _cacheMap[tid] = index; // 可以直接根据_cacheMap的Size获取未分配缓存列表的索引
    }
    std::cout << tid << "\n";
    return _cacheList1[_cacheMap[tid]];
}
void DoubleCacheManager::periodicUpdateCaches(){ // 定期更新缓存
    // 合并, 从其他线程的缓存合并到_cacheList2[0]
    for(size_t idx = 1; idx < _cacheList2.size(); ++idx){
        auto &pendingUpdateList = _cacheList2[idx].getPendingUpdateList();
        for(auto &[k, v] : pendingUpdateList){
            if(_cacheList2[0].isExist(k)){
                _cacheList2[0].getValue(k); // 访问一次，更新LRU
            }else{
                _cacheList2[0].addElement(k, v); // 添加到_cacheList2[0]
            }
        }
        pendingUpdateList.clear(); // 清空pendingUpdateList
    }
    _cacheList2[0].getPendingUpdateList().clear(); // 清空pendingUpdateList
    LogInfo(">>> 已合并，将缓存写入磁盘文件.");
    _cacheList2[0].writeToFile(Configuration::getInstance().getparameter("cache_path")); // 写入磁盘文件

    // 同步, 从_cacheList2[0]同步到其他线程的缓存
    for(size_t idx = 1; idx < _cacheList2.size(); ++idx){
        _cacheList2[idx].update(_cacheList2[0]);
    }
    // swap 加锁， 获取所有的锁
    {
        std::cout << "-------------------------交换Cache-------------------------\n";
        std::vector<std::unique_lock<std::mutex>> locks;
        locks.reserve(_cache_manager_mutexs.size());
        for(std::mutex &mtx : _cache_manager_mutexs){
            locks.emplace_back(mtx);
        }
        std::swap(_cacheList1, _cacheList2);
    }
}

std::mutex& DoubleCacheManager::getMutex(const std::thread::id & tid){
    return _cache_manager_mutexs[_cacheMap[tid]];
}

DoubleCacheManager *DoubleCacheManager::_instance = nullptr;
pthread_once_t DoubleCacheManager::_once = PTHREAD_ONCE_INIT;