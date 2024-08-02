#include "../../include/online/LRUCache.hh"
#include "../../include/online/Configuration.hh"
#include "../../include/online/LogSingleTon.hh"

#include <fstream>
#include <sstream>
#include <iostream>

using std::istringstream;
using std::ifstream, std::ofstream;
using std::make_pair;
LRUCache::LRUCache()
: _capacity(std::stoi(Configuration::getInstance().getparameter("cache_capacity"))) 
{
    std::cout << "LRUCache capacity: " << _capacity << "\n";
}

LRUCache::LRUCache(const LRUCache& rhs){
    this->_capacity = rhs._capacity;
    this->_hashMap = rhs._hashMap;
    this->_resultsList = rhs._resultsList;
    this->_pendingUpdateList = rhs._pendingUpdateList;
}

bool LRUCache::isExist(const string& key){ // 判断是否包含key
    return _hashMap.count(key);
} 
string LRUCache::getValue(const string& key){
    // 获取value
    _resultsList.splice(_resultsList.begin(), _resultsList, _hashMap[key]);
    string value = _hashMap[key]->second;
    _pendingUpdateList.push_back(make_pair(key, value));
    return value;
}

void LRUCache::addElement(const string &key, const string &value){
    
    if(_hashMap.count(key)){ // key存在，则更新key value
        _resultsList.splice(_resultsList.begin(), _resultsList, _hashMap[key]);
        _hashMap[key]->second = value;
        return;
    }

    if(_resultsList.size() == _capacity){ // 若达到容量上限，则删除最不常用的key
        _hashMap.erase(_resultsList.back().first); 
        _resultsList.pop_back();
    }
    _resultsList.push_front(make_pair(key, value));
    _hashMap[key] = _resultsList.begin();
    _pendingUpdateList.push_back(make_pair(key, value));
}

void LRUCache::readFromFile(const string &fileName){ // 预热, 从磁盘读取保存的缓存
    ifstream ifs(fileName);
    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string key, value;
        iss >> key >> value;
        _resultsList.push_back({key, value});
        _hashMap[key] = std::prev(_resultsList.end(), 1);
    }
    ifs.close();
}

void LRUCache::writeToFile(const string &fileName){ // 将缓存写入磁盘, 用于持久化
    ofstream ofs(fileName);
    for(auto &[k, v] : _resultsList){
        ofs << k << " " << v << "\n";
    }
    ofs.close();
}

void LRUCache::update(const LRUCache &rhs){ // 更新缓存
    this->_capacity = rhs._capacity;
    this->_hashMap = rhs._hashMap;
    this->_resultsList = rhs._resultsList;
    this->_pendingUpdateList = rhs._pendingUpdateList;
}
list<pair<string, string>> & LRUCache::getPendingUpdateList(){ // 返回等待更新的节点信息
    return _pendingUpdateList;
}
