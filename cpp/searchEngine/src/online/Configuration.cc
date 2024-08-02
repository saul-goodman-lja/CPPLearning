#include "../../include/online/Configuration.hh"

#include <iostream>
#include <fstream>
#include <sstream>

Configuration &Configuration::getInstance(){
    static Configuration instance;
    return instance;
}
Configuration::Configuration(){
    init();
}

void Configuration::init(){
    // 加载配置文件
    std::ifstream _configFile;
    _configFile.open("/home/lja/user/CppLearning/cpp/searchEngine/conf/myconf.conf");

    string line;
    while(std::getline(_configFile, line)){
        string key, value, equal;
        std::istringstream iss(line);
        iss >> key >> equal >> value;
        _configMap[key] = value;
    }
    _configFile.close();

    // 加载停用词
    std::ifstream en_ifs(getparameter("english_stop_words"));
    std::ifstream cn_ifs(getparameter("chinese_stop_words"));
    string word;
    while(en_ifs >> word){
        _stop_words.insert(word);
    }
    while(cn_ifs >> word){
        _stop_words.insert(word);
    }
    en_ifs.close();
    cn_ifs.close();
}

string Configuration::getparameter(const string &key) const{
    if(_configMap.count(key)){
        return _configMap.at(key);
    }
    std::cerr << "key: " << key << " not found" << "\n";
    return "";
}