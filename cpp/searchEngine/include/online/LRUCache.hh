#ifndef __LRUCACHE_HH__
#define __LRUCACHE_HH__

#include <list>
#include <unordered_map>
#include <utility>
#include <string>

using std::string, std::pair, std::unordered_map, std::list;

class LRUCache{
public:
    LRUCache(); // 构造函数
    LRUCache(const LRUCache&); // 深拷贝
    bool isExist(const string& key); // 判断是否包含key
    string getValue(const string& key); // 获取value
    void addElement(const string &key, const string &value); // 添加 key - value

    void readFromFile(const string &fileName); // 预热, 从磁盘读取保存的缓存
    void writeToFile(const string &fileName); // 将缓存写入磁盘, 用于持久化

    void update(const LRUCache &rhs); // 更新缓存
    list<pair<string, string>> & getPendingUpdateList(); // 返回等待更新的节点信息
private:
    unordered_map<string, list<pair<string, string>>::iterator> _hashMap; // 采用 hashTable进行查找
    list<pair<string, string>> _resultsList; // 保存键值对
    list<pair<string, string>> _pendingUpdateList; // 等待更新的节点信息
    int _capacity; // 容量  
};

#endif