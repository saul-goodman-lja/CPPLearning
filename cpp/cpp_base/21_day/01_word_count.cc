#include <algorithm>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using std::cin, std::cout, std::endl;
using std::ifstream, std::ofstream, std::map;
using std::istringstream, std::string;

class Dictionary{
public:
    Dictionary() = default;
    void insert(const string &);
    void read(const string &);
    void store(const string &);
private:
    map<string, int> _dict;
};

void processWord(string & word){

    auto removeComparator = [](char c){
        return !std::isalpha(c);
    };

    word.erase(std::remove_if(word.begin(), word.end(), removeComparator), word.end());
}

void Dictionary::insert(const string & word){
    _dict[word]++;
}

void Dictionary::read(const string & filename){

    ifstream ifs(filename);

    if(!ifs){
        std::cerr << "ifs open file failed!" << std::endl;
        return ;
    }

    string line;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string word;
        while(iss >> word){
            processWord(word);
            if(word.size()){
                insert(word);
            }
        }
    }

    ifs.close();
}

void Dictionary::store(const string &filename){
    ofstream ofs(filename);
    for(const auto & word :_dict){
        ofs << word.first << " " << word.second << endl;
    }
}

int main(void){

    auto start = std::chrono::high_resolution_clock::now();
    Dictionary dict;
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