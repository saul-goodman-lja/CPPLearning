#include <iostream>
#include <functional>
#include <vector>
#include <string>

using std::cin, std::cout, std::endl;

void test(){

    std::string str = "aab";

    std::string text = "leetcode";
    std::vector<int> next(str.size());
    std::function<void()> getNext = [&](){
        int j = 0, k = -1;
        next[0] = -1;
        int n = str.size();
        while(j < n - 1){
            if(k == -1 || str[j] == str[k]){
                next[++j] = ++k;
            }else{
                k = next[k];
            }
        }
    };
    // getNext();

    // nextVal 数组
    std::vector<int> nextVal(str.size());
    std::function<void()> getNextVal = [&] () -> void {
        int j = 0, k = -1;
        nextVal[0] = -1;
        int n = str.size();
        while(j < n - 1){
            if(k == -1 || str[j] == str[k]){
                ++j, ++k;
                if(str[j] != str[k]){
                    nextVal[j] = k;
                }else{
                    nextVal[j] = nextVal[k];
                }
            }else{
                k = nextVal[k];
            }
        }
    };  

    getNextVal();
    // int i = 0, j = 0;
    // int m = text.size(), n = str.size();
    // while(i < m){
    //     if(j == -1 || text[i] == str[j]){
    //         i++;
    //         j++;
    //     }else{
    //         j = nextVal[j];
    //     }

    //     if(j >= n){
    //         cout << i - j << endl;
    //         break;
    //     }
    // }
    
    for(int i = 0; i < nextVal.size(); i++){
        cout << nextVal[i] << " ";
    }

    // cout << "not match" << endl;
}

int main(){

    test();
    return 0;
}