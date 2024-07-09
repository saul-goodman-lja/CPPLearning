#include <iostream>
#include <functional>
#include <vector>
#include <string>

using std::cin, std::cout, std::endl;

void test(){

    std::string str = "leete";

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
    getNext();

    int i = 0, j = 0;
    while(i < text.size()){
        if(j == -1 || text[i] == str[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }

        if(j >= str.size()){
            cout << i - j << endl;
            break;
        }
    }

    cout << "not match" << endl;
}

int main(){

    test();
    return 0;
}