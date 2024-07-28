#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using std::cin, std::cout;
using std::map, std::set;
using std::ofstream, std::ifstream;
using std::string;
using std::istringstream;

int main(){
    map<string, set<int>> index_dict;
    ifstream ifs("../dict.dat");
    if(!ifs.is_open()){
        cout << "file not found" << std::endl;
        return 0;
    }
    string line;
    int i = 0;
    while(std::getline(ifs, line)){
        istringstream iss(line);
        string word;
        int t;
        while(iss >> word >> t){
            for(char c : word){
                index_dict[string(1, c)].insert(i);
            }
        }
        i++;
    }
    ofstream ofs("../dictIndex.dat");
    for(auto &[key, value] : index_dict){
        cout << key << "\n";
        ofs << key << " ";
        for(auto &v : value){
            ofs << v << " ";
        }
        ofs << "\n";
    }
}