#include <iostream>
#include <fstream>
#include <string>
#include "UnionFind.h"

int main(){
    std::ifstream file("tinyUF.txt");
    if(!file.is_open()){
        std::cerr <<"u" << std::endl;
        return 1;
    }
        
    int N;
    file >> N;

    int p, q;
    while(file >> p >> q){

        if(uf.connected(p, q)){
            uf.unionSets(p, q);
            std::cout << p << " " << q << std::endl;
        }

    }
    file.close();

    return 0;
}