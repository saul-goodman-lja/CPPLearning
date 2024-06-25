#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>

using std::string, std::istringstream;
using std::vector, std::ifstream ,std::ofstream;

struct Record{
    string _word;
    int _frequency;
    Record(string word, int num) : _word(word), _frequency(num) {}
};

class Dictionary{
public:
    Dictionary(int capacity){
        _dict.reserve(capacity);
    }

    void insert(const string& word){
        // for(auto & record : _dict){
        //     if(record._word == word){
        //         record._frequency++;
        //         return ;
        //     }
        // }
        auto it = std::lower_bound(_dict.begin(), _dict.end(), word, 
                                   [](const Record& a, const std::string& b) { return a._word < b; });
        if (it != _dict.end() && it->_word == word) {
            // 元素已存在，增加频率
            it->_frequency++;
        }else{
            _dict.insert(it,Record(word, 1));
        }
        // _dict.emplace_back(word, 1);
        // std::sort(_dict.begin(), _dict.end(), [](Record a, Record b) { return a._word < b._word; });
    }
    
    void read(const string & filename);
    void store(const string & filename);

private:
    vector<Record> _dict;
};

void processWord(string & word){

    auto removeComparator = [](char c){
        return !std::isalpha(c);
    };

    word.erase(std::remove_if(word.begin(), word.end(), removeComparator), word.end());
}


void Dictionary::read(const string & filename){
    ifstream ifs(filename);
    if(!ifs){
        std::cerr << "ifs open file failed!" << std::endl;
        return ;
    }

    string line;
    while(ifs >> line){
        istringstream iss(line);
        string word;
        while(iss >> word){
            processWord(word);
            if(word.size()){
                insert(word);
            }
        }
    }

    // std::sort(_dict.begin(), _dict.end(), [](Record a, Record b){ return a._word < b._word; });
    // std::sort(_dict.begin(), _dict.end(), [](Record a, Record b){ return a._frequency > b._frequency; });

    ifs.close();
}

void Dictionary::store(const string & filename){
    ofstream ofs(filename);
    for(const auto & element : _dict){
        ofs << element._word << " " << element._frequency << std::endl;
    }
}

int main(void) {
    auto start = std::chrono::high_resolution_clock::now();
    Dictionary dict(13000);
    dict.read("The_Holy_Bible.txt");
    dict.store("dict.txt");
    auto end = std::chrono::high_resolution_clock::now();
     // 计算程序运行时间
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    double second = duration.count() / 1000000.0;
    // 输出程序运行时间（以微秒为单位）
    std::cout << "程序运行时间： " << second << " second" << std::endl;
    return 0;
}