#ifndef __SPLITTOOL_HH__
#define __SPLITTOOL_HH__

#include "../../src/simhash/Simhasher.hpp"
#include <vector>
#include <string>
#include <pthread.h>

using std::vector, std::string;

class SplitTool {
public:
    static SplitTool * createInstance();
    vector<string> cut(const string &sentence);
private:
    SplitTool();
    ~SplitTool() = default;
    SplitTool(const SplitTool &) = delete;
    SplitTool & operator=(const SplitTool &) = delete;
    static void init_r();
    static void destroy();
    static SplitTool * _instance;
    static pthread_once_t _once;
    cppjieba::Jieba _jieba;
};

#endif