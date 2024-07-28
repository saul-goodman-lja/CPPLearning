#ifndef __SPLITTOOL_HH__
#define __SPLITTOOL_HH__
#include <string>
#include <vector>
using std::string, std::vector;

class SplitTool {
public:
    virtual ~SplitTool() = default;
    virtual vector<string> cut(const string &sentence) = 0; //分词函数，纯虚函数，提供接口
};

#endif