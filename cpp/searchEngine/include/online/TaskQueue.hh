#ifndef _TASK_QUEUE_HH_
#define _TASK_QUEUE_HH_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <barrier>


using ElemType = std::function<void()>;

class TaskQueue{
public:
    TaskQueue(size_t);
    ~TaskQueue();
    void push(ElemType &&taskcb);
    ElemType pop();
    bool full() const;
    bool empty() const;
    void wakeup();
private:
    size_t _queSize;
    std::queue<ElemType> _que;
    std::mutex _mutex;
    std::condition_variable _notFull;
    std::condition_variable _notEmpty;
    bool _flag;
};

#endif