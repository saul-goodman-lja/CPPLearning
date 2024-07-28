#include <cctype>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cin, std::cout;
using std::ifstream, std::ofstream;
using std::istringstream, std::ostringstream;
using std::string;

void cleanFile(const string &path, const string &filename){
    ifstream in(path + filename);
    ofstream out(path + "/yuliao_clean/english.txt");
    string line;
    while (getline(in, line)){
        istringstream iss(line);
        string word;
        while (iss >> word){
            for (auto &c : word){
                if(::isalpha(c)){
                    // c = std::tolower(c);
                    c = std::isupper(c) ? c ^ ' ' : c; // ' ' = 32
                }else{
                    c = ' ';
                }
            }
            out << word << " ";
        }
        out << "\n";
    }
}

int main(){
    cleanFile("../resources/模块一/", "yuliao/english.txt");
    return 0;
}