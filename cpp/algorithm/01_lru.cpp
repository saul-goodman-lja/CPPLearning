#include <iostream>
#include <list>
#include <unordered_map>

/**
 * @brief LRU缓存机制的实现类
 * 
 * 该类基于双向链表和哈希表实现LRU（Least Recently Used）缓存机制。
 * 双向链表用于维护元素的使用顺序，最近使用的元素位于链表尾部。
 * 哈希表用于快速查找链表中的元素。
 */
class LRUCache{
private:
    int lru_capacity; /**< 缓存的容量 */
    std::list<std::pair<int, int>> cache_list; /**< 存储缓存数据的双向链表 */
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_map; /**< 哈希表用于快速定位链表中的元素 */

public:
    /**
     * @brief 构造函数
     * @param capacity 缓存的容量
     */
    LRUCache(int capacity) : lru_capacity(capacity){}
    
    /**
     * @brief 获取指定键的值
     * 
     * @param key 需要获取值的键
     * @return int 键对应的值，如果键不存在则返回-1
     */
    int get(const int key){
        // 如果键不存在于缓存中，则返回-1
        if(cache_map.find(key) == cache_map.end()){
            return -1;
        }
        
        // 将使用过的元素移动到链表尾部，表示最近使用
        cache_list.splice(cache_list.end(), cache_list, cache_map[key]);
        
        // 返回键对应的值
        return cache_map[key]->second;
    }

    /**
     * @brief 添加或更新缓存数据
     * 
     * @param key 缓存的键
     * @param value 缓存的值
     */
    void put(const int key, const int value){
        // 如果键已存在，则更新值并移动到链表尾部
        if(cache_map.find(key) != cache_map.end()){
            cache_map[key]->second = value;
            cache_list.splice(cache_list.end(), cache_list, cache_map[key]);
            return;
        }
        
        // 如果缓存已满，则移除最旧的元素（链表头部元素）
        if(cache_list.size() == lru_capacity){
            int key_to_remove = cache_list.front().first;
            cache_map.erase(key_to_remove);
            cache_list.pop_front();
        }
        
        // 添加新的元素到链表尾部，并更新哈希表
        cache_list.push_back({key, value});
        cache_map[key] = --cache_list.end();
    }

};

int main(void){

    return 0;
}