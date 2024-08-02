#include "../../include/online/SplitTool.hh"

#include "../../include/online/SplitTool.hh"
#include "../../include/online/Configuration.hh"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::istringstream;

SplitTool::SplitTool()
: _jieba(Configuration::getInstance().getparameter("jieba_dict_path"), Configuration::getInstance().getparameter("jieba_model_path"), Configuration::getInstance().getparameter("jieba_user_path")){}

SplitTool * SplitTool::createInstance(){
    pthread_once(&_once,init_r);
    return _instance;
}

vector<string> SplitTool::cut(const string &sentence){
    vector<string> words;
    _jieba.Cut(sentence, words, true);
    return words;
}

void SplitTool::init_r(){
    _instance = new SplitTool();
    atexit(destroy);
}
void SplitTool::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}

SplitTool *SplitTool::_instance = nullptr;
pthread_once_t SplitTool::_once = PTHREAD_ONCE_INIT;

// int main(){
//     vector<string> words = SplitTool::createInstance()->cut("今天天气不错");
//     for(auto &word : words){
//         std::cout << word << std::endl;
//     }
// }