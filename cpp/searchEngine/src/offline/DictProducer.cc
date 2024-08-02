#include "../../include/offline/DictProducer.hh"
#include "../../include/offline/Configuration.hh"

#include <cctype>

#include <fstream>
#include <sstream>
using std::ifstream, std::ofstream;
using std::istringstream;

DictProducer::DictProducer(const string &dir, SplitTool *split_tool)
: _cuttor(split_tool){}

DictProducer::~DictProducer() = default;
size_t DictProducer::nBytesCode(const char ch){
    if(ch & (1 << 7)){
        int nBytes = 1;
        for(int idx = 0; idx < 7; ++idx){
            if(ch & (1 << (6 - idx))){
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}
void DictProducer::buildEnDict()
{
    Configuration config;
    string english_yuliao = config.getparameter("english_yuliao");
    string dict_path = config.getparameter("dict_path");
    map<string, int> en_cnt;
    ifstream ifs(english_yuliao);
    string line;
    while(std::getline(ifs, line)){
        for (auto &c : line){
            if(::isalpha(c)){
                // c = std::tolower(c);
                c = std::isupper(c) ? c ^ ' ' : c; // ' ' = 32
            }else{
                c = ' ';
            }
        }
        istringstream iss(line);
        string word;
        while(iss >> word){
            if(!word.empty()){
                en_cnt[word]++;
            }
        }
    }
    ifs.close();
    string stop_path = config.getparameter("english_stop_words");
    ifstream ifs_stop(stop_path);
    string stop_word;
    while(ifs_stop >> stop_word){
        en_cnt.erase(stop_word);
    }
    ifs_stop.close();
    ofstream ofs(dict_path, std::ios::app);
    for(auto &[k, v] : en_cnt){
        ofs << k << " " << v << "\n";
    }
    ofs.close();
}

void DictProducer::buildCnDict()
{
    Configuration config;
    string dict_path = config.getparameter("dict_path");
    vector<string> chinese_words = _cuttor->cut("chinese_yuliao");
    map<string, int> ch_cnt;
    for(auto &word : chinese_words){
        if(!word.empty()){
            ch_cnt[word]++;
        }
    }

    string stop_path = config.getparameter("chinese_stop_words");
    ifstream ifs_stop(stop_path);
    string stop_word;
    while(ifs_stop >> stop_word){
        ch_cnt.erase(stop_word);
    }
    ifs_stop.close();
    ofstream ofs(dict_path, std::ios::app);
    for(auto &[k, v] : ch_cnt){
        ofs << k << " " << v << "\n";
    }
    ofs.close();
    std::cout << "词典已经生成到 " << dict_path << "\n";
}

void DictProducer::createIndex(){
    Configuration config;
    string dict_path = config.getparameter("dict_path");
    ifstream ifs(dict_path);
    string line;
    int i = 0;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string word;
        iss >> word;
        for(size_t idx = 0; idx < word.size();){
            size_t len = nBytesCode(word[idx]); // 每个字符要确定其所占的字节数
            _index[word.substr(idx, len)].insert(i);
            idx += len;
        }
        i++;
    }
    ifs.close();
    string dictIndex_path = config.getparameter("dictIndex_path");
    ofstream ofs(dictIndex_path);
    for(auto &[key, value] : _index){
        ofs << key << " ";
        for(auto &v : value){
            ofs << v << " ";
        }
        ofs << "\n";
    }
    std::cout << "词典索引已经生成到 " << dictIndex_path << "\n";
}

void DictProducer::store(const string &filepath){
    // deprecated
}