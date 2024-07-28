#include "../../include/offline/Configuration.hh"

#include <iostream>
#include <fstream>
#include <sstream>
Configuration::Configuration()
{
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
}

Configuration::~Configuration() = default;
string Configuration::getparameter(const string &key) const{
    if(_configMap.count(key)){
        return _configMap.at(key);
    }
    std::cerr << "key: " << key << " not found" << "\n";
    return "";
}