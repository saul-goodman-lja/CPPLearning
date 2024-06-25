#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache{
private:
    int lru_capacity;
    std::list<std::pair<int, int>> cache_list;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_map;

public:
    LRUCache(int capacity) : lru_capacity(capacity){}

    int get(const int key){
        
        if(cache_map.find(key) == cache_map.end()){
            return -1;
        }

        cache_list.splice(cache_list.end(), cache_list, cache_map[key]);

        return cache_map[key]->second;
    }

    void put(const int key, const int value){
        
        if(cache_map.find(key) != cache_map.end()){
            cache_map[key]->second = value;
            cache_list.splice(cache_list.end(), cache_list, cache_map[key]);
        } else {
            if(cache_list.size() == lru_capacity){
                int key_to_remove = cache_list.front().first;
                cache_map.erase(key_to_remove);
                cache_list.pop_front();
            }
            cache_list.push_back({key, value});
            cache_map[key] = --cache_list.end();
        }
    }

};

int main(void){

    return 0;
}