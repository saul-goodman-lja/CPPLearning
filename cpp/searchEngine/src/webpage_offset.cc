#include "../include/offline/Configuration.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using std::cin, std::cout, std::string;
using std::ifstream, std::ofstream, std::istringstream;
using std::vector;
int main(){
    Configuration conf;
    // string new_ripe_page = conf.getparameter("new_ripe_page");
    // string offset_path = conf.getparameter("new_offset");

    string new_ripe_page = conf.getparameter("new_ripe_page_deduplication");
    string offset_path = conf.getparameter("new_offset_deduplication");

    ifstream ifs(new_ripe_page);
    string line;

    size_t total = 0;
    size_t offsets = 0;
    vector<std::pair<int, int>> offset_index;
    while(std::getline(ifs,line)){
        if(line.find("<Webpage>") != string::npos){
            offsets = 0;
        }
        offsets += line.size() + 1;
        if(line.find("</Webpage>") != string::npos){
            offset_index.emplace_back(std::make_pair(total == 0 ? 0 : total, offsets));
            total += offsets;
        }
    }
    ofstream ofs(offset_path);
    for(auto &p : offset_index){
        ofs << p.first << " " << p.second << "\n";
    }
    ofs.close();
    ifs.close();
    std::cout << "已存储到 " << offset_path << "\n";

    // ifstream page(new_ripe_page);
    // ifstream ifs(offset_path);
    // int t = 10;
    // string line;
    // while(t-- && std::getline(ifs, line)){
    //     istringstream iss(line);
    //     size_t start = 0, offset = 0;
    //     iss >> start >> offset;
    //     page.seekg(start);
    //     char *content = new char[offset + 1]();
    //     page.read(content, offset);
    //     std::cout << string(content) << "\n";
    // }
    // page.close();
    // ifs.close();
}