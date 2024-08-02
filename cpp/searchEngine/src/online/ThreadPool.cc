#include "../../include/online/ThreadPool.hh"
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
,_taskQue(_queSize)
, _isExit(false){
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool() = default;

void ThreadPool::start(){
    for(size_t idx = 0; idx < _threadNum; idx++){
        std::thread th(&ThreadPool::doTask, this);
        _threads.push_back(std::move(th));
        // thread 只有移动构造， 只能传右值
        // _threads.emplace_back(std::thread(&ThreadPool::doTask, this));
    }
}

void ThreadPool::stop(){
    // while(!_taskQue.empty())
    // {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    _isExit = true;
    std::unique_lock<std::mutex> ul(_mutex);
    if(!_taskQue.empty()){
        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        _isEmpty_Exit.wait(ul);
    }
    ul.unlock();
    _taskQue.wakeup();

    for(auto & t : _threads){
        if(t.joinable()){
            t.join();
        }
    }
}

void ThreadPool::addTask(ElemType &&taskcb){
    if(taskcb){
        _taskQue.push(std::move(taskcb));
    }
}

ElemType ThreadPool::getTask(){
    return _taskQue.pop();
}

void ThreadPool::doTask(){
    while(!_isExit || !_taskQue.empty()){

        ElemType &&taskcb = getTask();
        if(taskcb){
            taskcb();
        }else{
            std::cout << "taskcb = nullptr" << std::endl;
        }
    }
    std::unique_lock<std::mutex> ul(_mutex);
    _isEmpty_Exit.notify_one();
}