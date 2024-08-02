#include "../../include/online/TaskQueue.hh"
#include <utility>
#include <thread>
#include <chrono>
TaskQueue::TaskQueue(size_t size)
: _queSize(size)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
, _flag(true) {}

TaskQueue::~TaskQueue() = default;

void TaskQueue::push(ElemType &&taskcb){
    std::unique_lock<std::mutex> ul(_mutex);
    while(full()){
        _notFull.wait(ul);
    }
    _que.push(std::move(taskcb));
    _notEmpty.notify_one();
}

// std::this_thread::sleep_for(std::chrono::nanoseconds(1));
ElemType TaskQueue::pop(){
    std::unique_lock<std::mutex> ul(_mutex);
    while(empty()){
        // std::this_thread::sleep_for(std::chrono::nanoseconds(100));
        if(!_flag){
            return nullptr;
        }
        _notEmpty.wait(ul);
    }
    ElemType rst = _que.front();
    _que.pop();
    _notFull.notify_one();
    return rst;
}

bool TaskQueue::full() const{
    return _que.size() == _queSize;
}

bool TaskQueue::empty() const{
    return 0 == _que.size();
}

void TaskQueue::wakeup(){
    std::unique_lock<std::mutex> ul(_mutex);
    _flag = false;
    _notEmpty.notify_all();
}
