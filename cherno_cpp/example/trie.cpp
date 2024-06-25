#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

using std::cout;

class Trie{
private:
    std::unordered_map<char, std::unique_ptr<Trie>> data;
    bool is_end{false};
public:
    Trie(){}

    void insert(std::string word){
        Trie *cur = this;
        for(char c : word){
            if(cur->data.find(c) == cur->data.end()){
                cur->data[c] = std::make_unique<Trie>();
            }
            cur = cur->data[c].get();
        }
        cur->is_end = true;
    }

    bool search(const std::string &word){
        const Trie *cur = this;
        for(char c : word){
            if(cur->data.find(c) == cur->data.end()){
                return false;
            }
            cur = cur->data.at(c).get();
        }
        return cur->is_end;
    }

    bool startsWith(const std::string &prefix) const{
        const Trie *cur = this;
        for(char c : prefix){
            if(cur->data.find(c) == cur->data.end()){
                return false;
            }
            cur = cur->data.at(c).get();
        }
        return true;
    }

};

int main(){
    Trie trie;
    
    trie.insert("apple");
    cout << std::boolalpha << trie.search("apple") << std::endl; // 输出 true
    cout << std::boolalpha << trie.search("app") << std::endl;   // 输出 false
    cout << std::boolalpha << trie.startsWith("app") << std::endl; // 输出 true

    return 0;
}