#ifndef __CONFIGURATION_HH__
#define __CONFIGURATION_HH__

#include <string>
#include <fstream>
#include <unordered_map>

using std::string;
using std::unordered_map;
class Configuration{
public:
    Configuration();
    ~Configuration();
    string getparameter(const string &key) const;
private:
    unordered_map<string, string> _configMap;
};

#endif