#include "../../include/online/ProgressCache.hh"

#include <iterator>
#include <iostream>
using std::make_pair;
ProgressCache::ProgressCache()
: _capacity(100) {}

ProgressCache * ProgressCache::getInstance() {
    pthread_once(&_once,init_r);
    return _instance;
}

void ProgressCache::init_r(){
    _instance = new ProgressCache();
    atexit(destroy);
}

void ProgressCache::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}

bool ProgressCache::isExist(const string& key){
    return _cache_map.count(key);
}
string ProgressCache::getValue(const string& key){
    _cache_list.splice(_cache_list.begin(), _cache_list, _cache_map[key]);
    std::cout << "最常用的key: " << _cache_list.begin()->first << " value: " << _cache_list.begin()->second << std::endl;
    return _cache_map[key]->second;
}
void ProgressCache::putKeyValue(const string& key, const string& value){
    if(_cache_map.count(key)){ // key存在，则更新key value
        _cache_map[key]->second = value;
        _cache_list.splice(_cache_list.begin(), _cache_list, _cache_map[key]);
        return;
    }

    if(_cache_list.size() == _capacity){ // 若达到容量上限，则删除最不常用的key
        string key_to_remove = _cache_list.back().first;
        _cache_list.pop_back();
        _cache_map.erase(key_to_remove);
    }
    _cache_list.push_front(make_pair(key,value));
    _cache_map[key] = _cache_list.begin();
    std::cout << "最常用的key: " << _cache_list.begin()->first << " value: " << _cache_list.begin()->second << std::endl;

}

std::mutex & ProgressCache::getMutex(){
    return _mutex;
}

ProgressCache *ProgressCache::_instance = nullptr;
pthread_once_t ProgressCache::_once = PTHREAD_ONCE_INIT;
