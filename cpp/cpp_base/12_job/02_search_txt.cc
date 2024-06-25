#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using std::cin, std::cout, std::endl, std::string, std::istringstream;
using std::ifstream, std::ofstream;
using std::vector, std::map, std::set;

class TextQuery{
public:
    void read(const string &);
    void query(const string &);
private:
    void insert(const string &, const int);
private:
    vector<string> _lines;
    map<string, set<int>> _wordNumbers;
    map<string, int> _dict;
};

void processWord(string & word){

    auto removeComparator = [](char c){
        return !std::isalpha(c);
    };
    word.erase(std::remove_if(word.begin(), word.end(), removeComparator), word.end());
}

void TextQuery::insert(const string & word, const int line){

    _dict[word]++;
    _wordNumbers[word].insert(line);
}

void TextQuery::read(const string &filename){

    ifstream ifs(filename);
    if(!ifs){
        std::cerr << "ifs open file if failed" << endl;
        return ;
    }

    int line = 1;

    string lineStr;
    while(std::getline(ifs, lineStr)){
        _lines.emplace_back(lineStr);
        istringstream iss(lineStr);
        string word;
        while(iss >> word){
            processWord(word);
            if(word.size()){
                insert(word, line);
            }
        }
        line++;
    }
    ifs.close();
}

void TextQuery::query(const string & word){

    cout << "---------------------------------------------" << endl;
    cout << word << " occurs " << _dict[word] << " times." << endl;
    for(const auto & line : _wordNumbers[word]){
        cout << "(line " << line << ") " << _lines[line - 1] << endl;
    }
    cout << "---------------------------------------------" << endl;
}

int main(int argc, char *argv[]){

    string queryWord = "and";
    
    TextQuery tq;
    tq.read("china_daily.txt");
    tq.query(queryWord);

    return 0;
}
