#include "MutexLockGurad.hh"
#include "Condition.hh"
#include "MutexLock.hh"
#include <iostream>
#include <thread>

using std::cin, std::cout, std::endl;

int cnt = 0;
void add(){
    while(cnt < 10000000){
        MutexLock lock;
        lock.init(nullptr);
        lock.lock();
        cnt++;
        lock.unlock();
    }
}
void test(){
    std::thread t1(add);
    t1.join();
    cout << "cnt = " << cnt << endl;
}

int main(){
    test();
    return 0;
}
