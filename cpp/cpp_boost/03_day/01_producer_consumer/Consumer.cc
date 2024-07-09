#include "Consumer.hh"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <condition_variable>

std::mutex printMutex;
std::condition_variable printCond;
void Consumer::consume(TaskQueue &taskQue){
    int cnt = 1000000;
    while(cnt--){
        int num = taskQue.pop();
        std::unique_lock<std::mutex> lg(printMutex);
        printCond.wait(lg);
        std::cout << "thread " << std::this_thread::get_id() 
        << " consume-- " << num << std::endl;
        lg.unlock();
        // sleep(1);
    }
}