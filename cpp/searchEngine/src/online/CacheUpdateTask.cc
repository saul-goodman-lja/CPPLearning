#include "../../include/online/CacheUpdateTask.hh"
#include "../../include/online/CacheManager.hh"
#include "../../include/online/DoubleCacheManager.hh"

// 执行定时器线程 时间到达后要执行的函数
void CacheUpdateTask::process(){
    // 定时器管理缓存
    // CacheManager::getInstance()->periodicUpdateCaches();

    // 双缓存
    DoubleCacheManager::getInstance()->periodicUpdateCaches();
}