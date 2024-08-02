#ifndef _THREADPOOL_HH_
#define _THREADPOOL_HH_

#include "TaskQueue.hh"
#include <vector>
#include <thread>
#include <chrono>

class ThreadPool{
public:
    ThreadPool(size_t, size_t);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(ElemType &&);
    ElemType getTask();
    void doTask();
private:
    size_t _threadNum;
    size_t _queSize;
    std::vector<std::thread> _threads;
    TaskQueue _taskQue;
    bool _isExit;     
    std::condition_variable _isEmpty_Exit;
    std::mutex _mutex;
};

#endif