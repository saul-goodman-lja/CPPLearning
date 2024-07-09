#include "TaskQueue.hh"
#include <iostream>
#include <unistd.h>
#include <queue>
#include <time.h>
#include <thread>
#include <mutex>
#include <condition_variable>

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize){}

TaskQueue::~TaskQueue(){}
void TaskQueue::push(const int & value){
    std::unique_lock<std::mutex> ul(_mutex);
    while(full()){
        _notFull.wait(ul);
    }
    _que.push(value);
    ul.unlock();
    _notEmpty.notify_one();
}
int TaskQueue::pop(){
    std::unique_lock<std::mutex> ul(_mutex);
    while(empty()){
        _notEmpty.wait(ul);
    }
    int top = _que.front();
    _que.pop();
    ul.unlock();
    _notFull.notify_one();
    return top;
}
bool TaskQueue::full(){
    return _que.size() == _queSize;
}
bool TaskQueue::empty(){
    return 0 == _que.size();
}