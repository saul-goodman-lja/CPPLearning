#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using std::cin, std::cout, std::vector, std::pair;
using std::string, std::istringstream;

class ShoppingCart{
public:
    static ShoppingCart * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new ShoppingCart();
        }
        return _pInstance;
    }
    
    void insert(const string& name, const int num){
        for(auto & item : _goodCount){
            if(item.first == name){
                item.second += num;
                return;
            }
        }
        _goodCount.push_back({name, num});
    }
    
    void print(){
        for(const auto & vec : _goodCount){
            cout << vec.first << " " << vec.second << "\n";
        }
    }
    
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

private:
    ShoppingCart(){}
    
    ~ShoppingCart(){
        
    }
    
    ShoppingCart(const ShoppingCart& rhs) = delete;
    ShoppingCart& operator=(const ShoppingCart& rhs) = delete;
    
    vector<pair<string, int>> _goodCount;
    static ShoppingCart *_pInstance;
};
ShoppingCart * ShoppingCart::_pInstance = nullptr;

int main(void){
    
    string line;
    while(getline(cin, line)){
        istringstream iss(line);
        string name;
        int num;
        iss >> name >> num;
        ShoppingCart::getInstance()->insert(name, num);
    }
    ShoppingCart::getInstance()->print();
    
    return 0;
}
