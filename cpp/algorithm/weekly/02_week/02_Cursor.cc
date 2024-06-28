#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

using std::string;
using std::cin, std::cout, std::endl;
using std::unordered_map;
using std::istringstream;

class Solution{
public:
    Solution(string s = "", int p = 0) : ans(s), pos(p){}
    void insert(const string &str){
        string pre = ans.substr(0, pos);
        string last = ans.substr(pos);
        ans = pre + str;
        ans += last;
        pos = pre.size() + str.size();
    }
    void move(const int cnt){
        if(pos + cnt >= 0 && pos + cnt <= ans.size()){
            pos += cnt;
        }
    }
    void delete_(const int len){
        if(len >=0 && len <= pos){
            string last = ans.substr(pos);
            string pre = ans.substr(0, pos - len);
            pos -= len;
            ans = pre + last;
        }
    }
    void copy(){
        string pre = ans.substr(0, pos);
        ans = pre + ans;
    }
    void print(){
        cout << ans.substr(0, pos) << "|" << ans.substr(pos) << endl;
    }
private:
    std::string ans;
    int pos;
};

enum{
    INSERT = 1,
    MOVE,
    DELETE,
    COPY,
    END
};
int main(void){
    unordered_map<string, int> hash;
    hash["insert"] = INSERT;
    hash["move"] = MOVE;
    hash["delete"] = DELETE;
    hash["copy"] = COPY;
    hash["end"] = END;
    Solution slu;
    istringstream iss;
    string line;
    while(true){
        std::getline(cin, line);
        string operate;
        iss.clear();
        iss.str(line);
        iss >> operate;
        bool is_end = false;
        string target;
        switch (hash[operate]){
            case INSERT:
                iss >> target;
                slu.insert(target);
                break;
            case MOVE:
                int cnt;
                iss >> cnt;
                slu.move(cnt);
                break;
            case DELETE:
                int len;
                iss >> len;
                slu.delete_(len);
                break;
            case COPY:
                slu.copy();
                break;
            case END:
                slu.print();
                is_end = true;
                break;
        }
        if(is_end){
            break;
        }
    }
    
    return 0;
}
// 注释的颜色