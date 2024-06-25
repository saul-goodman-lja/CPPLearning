#include <algorithm>
#include <iostream>
#include <string>

using std::cin, std::cout, std::string;

string minusString(const string& a, const string& b){
    int distence = a.length() - b.length();
    int c = 0;
    string rst = "";
    int i;
    for(i = a.length() - 1; i >= distence; i--){
        int j = i - distence;
        if(a[i] - c >= b[j]){
            rst += a[i] - b[j] + '0' - c;
            c = 0;
        }else{
            rst += a[i] - b[j] + 10 + '0' - c;
            c = 1;
        }
    }
    for(; i >=0; i--){
        if(a[i] - '0' >= c){
            rst += a[i]  - c;
            c = 0;
        }
        else{
            rst += a[i] + 10 - c;
            c = 1;
        }
    }
    return rst;
}

string calMinus(const string& a, const string& b){
    int aLen = a.length();
    int bLen = b.length();
    bool is_negative = false;
    string rst = "";
    if(aLen < bLen || aLen == bLen && a[aLen - bLen] < b[0]){
        is_negative = true;
        rst = minusString(b, a);
    }else{
        rst = minusString(a, b);
    }
    string minus = "";
    if(is_negative){
        minus += '-';
    }
    std::reverse(rst.begin(), rst.end());
    int i;
    for(i = 0; i < rst.length(); i++){
        if(rst[i] >= '1' && rst[i] <= '9'){
            break;
        }
    }
    rst = rst.substr(i);
    rst = minus + rst;
    return rst;
}

int main(void){
    
    string num1, num2;
    cin >> num1 >> num2;
    string rst = calMinus(num1, num2);
    cout << rst << "\n";
    return 0;
}