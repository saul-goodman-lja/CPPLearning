#include <iostream>
#include <unistd.h>

using std::cout;

int main(){

    cout << "a" << std::flush;
    // std::flush(cout);
    sleep(3);

}