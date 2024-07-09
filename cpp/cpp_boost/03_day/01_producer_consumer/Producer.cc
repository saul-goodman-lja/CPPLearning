#include "Producer.hh"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <thread>

extern std::mutex printMutex;
extern std::condition_variable printCond;
void Producter::produce(TaskQueue &taskQue){
    int cnt = 1500000;
    ::srand(::clock());
    while(cnt--){
        int num = rand() % 100;
        taskQue.push(num);
        std::unique_lock<std::mutex> lg(printMutex);
        std::cout << "thread " << std::this_thread::get_id() 
        << " produce---- " << num << std::endl;
        lg.unlock();
        printCond.notify_one();
        // sleep(1);
    }
}