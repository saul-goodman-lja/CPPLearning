#include "../../include/online/CacheManager.hh"
#include "../../include/online/Configuration.hh"
#include "../../include/online/LogSingleTon.hh"

#include <iostream>

CacheManager * CacheManager::getInstance(){
    pthread_once(&_once,init_r);
    return _instance;
}

void CacheManager::init_r(){
    _instance = new CacheManager();
    atexit(destroy);
}

void CacheManager::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}

CacheManager::CacheManager()
: _cacheList(std::stoi(Configuration::getInstance().getparameter("threadNum")))
, _cache_manager_mutexs(std::stoi(Configuration::getInstance().getparameter("threadNum")))
{
    initCache();
}
void CacheManager::initCache(){ // 从磁盘文件中读取缓存信息
     _cacheList[0].readFromFile(Configuration::getInstance().getparameter("cache_path"));
     for(size_t idx = 1; idx < _cacheList.size(); ++idx){
        _cacheList[idx].update(LRUCache(_cacheList[0]));
     }
}
LRUCache & CacheManager::getCache(const std::thread::id &tid){ // 获取某个线程的缓存
    // 如果线程Id 还未和缓存关联，则映射到缓存列表中还未分配的LRUCache
    if(!_cacheMap.count(tid)){ 
        size_t index = _cacheMap.size();
        _cacheMap[tid] = index; // 可以直接根据_cacheMap的Size获取未分配缓存列表的索引
    }
    std::cout << tid << "\n";
    return _cacheList[_cacheMap[tid]];
}
void CacheManager::periodicUpdateCaches(){ // 定期更新缓存
    // 合并, 从其他线程的缓存合并到_cacheList[0]
    {
        // 加锁，获取所有锁
        std::vector<std::unique_lock<std::mutex>> locks;
        locks.reserve(_cache_manager_mutexs.size());
        for(std::mutex &mtx : _cache_manager_mutexs){
            locks.emplace_back(mtx);
        }
        LogInfo("---已上锁，准备合并缓存---");
        for(size_t idx = 1; idx < _cacheList.size(); ++idx){
            auto &pendingUpdateList = _cacheList[idx].getPendingUpdateList();
            for(auto &[k, v] : pendingUpdateList){
                if(_cacheList[0].isExist(k)){
                    _cacheList[0].getValue(k); // 访问一次，更新LRU
                }else{
                    _cacheList[0].addElement(k, v); // 添加到_cacheList[0]
                }
            }
            pendingUpdateList.clear(); // 清空pendingUpdateList
        }
        _cacheList[0].getPendingUpdateList().clear(); // 清空pendingUpdateList
    }
    LogInfo("---缓存合并完毕，已解锁---");
    _cacheList[0].writeToFile(Configuration::getInstance().getparameter("cache_path")); // 写入磁盘文件

    // 同步, 从_cacheList[0]同步到其他线程的缓存
    {
        std::vector<std::unique_lock<std::mutex>> locks;
        locks.reserve(_cache_manager_mutexs.size());
        for(std::mutex &mtx : _cache_manager_mutexs){
            locks.emplace_back(mtx);
        }
        LogInfo("---已上锁，准备同步缓存---");
        for(size_t idx = 1; idx < _cacheList.size(); ++idx){
            _cacheList[idx].update(_cacheList[0]);
        }
    }
    LogInfo("---缓存同步完毕，已解锁---");
}

std::mutex& CacheManager::getMutex(const std::thread::id & tid){
    return _cache_manager_mutexs[_cacheMap[tid]];
}

CacheManager *CacheManager::_instance = nullptr;
pthread_once_t CacheManager::_once = PTHREAD_ONCE_INIT;