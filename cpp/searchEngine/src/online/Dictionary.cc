#include "../../include/online/Dictionary.hh"
#include "../../include/online/Configuration.hh"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::istringstream;

Dictionary::Dictionary(){
    init();
}

Dictionary * Dictionary::createInstance(){
    pthread_once(&_once,init_r);
    return _instance;
}
void Dictionary::init_r(){
    _instance = new Dictionary();
    atexit(destroy);
}
void Dictionary::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}
void Dictionary::init (){
    _dict.reserve(50000);
    string dict_path = Configuration::getInstance().getparameter("dict_path");
    string dictIndex_path = Configuration::getInstance().getparameter("dictIndex_path");
    string line;
    ifstream ifs_dict(dict_path);
    while (std::getline(ifs_dict, line))
    {
        istringstream iss(line);
        string word;
        int cnt;
        while (iss >> word >> cnt)
        {
            _dict.push_back(std::make_pair(word, cnt));
        }
    }
    ifstream ifs_index(dictIndex_path);
    while (std::getline(ifs_index, line))
    {
        istringstream iss(line);
        string word;
        iss >> word;
        int index;
        while (iss >> index)
        {
            _index[word].insert(index);
        }
    }
    ifs_dict.close();
    ifs_index.close();
}
vector<pair<string, int>> & Dictionary::getDict(){
    return _dict;
}
map<string, set<int>> & Dictionary::getIndexTable(){
    return _index;
}

Dictionary *Dictionary::_instance = nullptr;
pthread_once_t Dictionary::_once = PTHREAD_ONCE_INIT;