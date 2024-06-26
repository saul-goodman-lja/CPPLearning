#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using std::cin ,std::cout, std::endl;
using std::string, std::map;
using std::ifstream, std::ofstream, std::istringstream;
map<string, string> buildMap(ifstream &map_file){
    map<string, string> trans_map;
    string key, value;
    while(map_file >> key && std::getline(map_file, value)){
        if(value.size() > 1){
            trans_map[key] = value.substr(1);
        }else{
            throw std::runtime_error("no rule for" + key);
        }
    }
    return trans_map;
}

const string & transform(const string &s, const map<string, string> &m){
    auto it = m.find(s);
    if(it != m.end()){
        return it->second;
    }else{
        return s;
    }
}

void word_transform(ifstream &map_file, ifstream &input){
    auto trans_map = buildMap(map_file);
    string line;
    while(std::getline(input, line)){
        istringstream iss(line);
        string word;
        while(iss >> word){
            cout << transform(word, trans_map) << " ";
        }
        cout << endl;
    }
}

void test(const string& map_filename, const string & process_filename){
    ifstream map_file(map_filename);
    if(!map_file){
        std::cerr << "can't open " << map_filename << endl;
        return ;
    }
    ifstream input(process_filename);
    if(!input){
        std::cerr << "can't open " << process_filename << endl;
        return;
    }
    word_transform(map_file, input);
}

int main(int argc, char *argv[]){

    if(argc != 3){
        std::cerr << "argc must be 3!" << endl;
        exit(1);
    }
    test(argv[1], argv[2]);
    return 0;
}
