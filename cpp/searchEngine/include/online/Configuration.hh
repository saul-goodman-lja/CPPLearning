#ifndef __CONFIGURATION_HH__
#define __CONFIGURATION_HH__

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::unordered_map;
using std::unordered_set;

// 配置类，读取配置文件，单例
class Configuration{
public:
    static Configuration &getInstance();
    string getparameter(const string &key) const; // 获取该key对应的配置信息
    void init();
public:
    std::unordered_set<string> _stop_words;
private:
    Configuration();
    ~Configuration() = default;
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;

    unordered_map<string, string> _configMap; // 保存该key对应的配置信息
};

#endif