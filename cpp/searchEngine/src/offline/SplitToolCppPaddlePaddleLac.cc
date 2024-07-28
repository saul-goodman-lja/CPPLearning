#include "../../include/offline/Configuration.hh"
#include "../../include/offline/SplitToolCppPaddlePaddleLac.hh"

#include <cstdlib>
#include <iostream>
#include <fstream>

using std::ifstream;

SplitToolCppPaddlePaddleLac::SplitToolCppPaddlePaddleLac(Configuration &conf)
: _conf(conf)
{
    
}
SplitToolCppPaddlePaddleLac::~SplitToolCppPaddlePaddleLac() = default;
vector<string> SplitToolCppPaddlePaddleLac::cut(const string & chinese_yuliao){
    string yuliaoPath = _conf.getparameter(chinese_yuliao);
    string split_path = _conf.getparameter("chinese_split");
    string command = "python3 lac.py " + yuliaoPath + " " + split_path;
    ::system(command.c_str());
    vector<string> result;
    ifstream ifs(split_path);
    while(ifs){
        string word;
        ifs >> word;
        result.emplace_back(word);
    }
    ifs.close();
    return result;
}

// int main(){
//     Configuration conf;
//     SplitToolCppPaddlePaddleLac split(conf);
//     split.cut("chinese_yuliao"); // 文件夹路径
//     return 0;
// }