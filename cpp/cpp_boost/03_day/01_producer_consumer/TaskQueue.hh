#ifndef _TASKQUEUE_HH_
#define _TASKQUEUE_HH_

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

class TaskQueue{
public:
    TaskQueue(size_t);
    ~TaskQueue();
    void push(const int &);
    int pop();
    bool full();
    bool empty();
private:
    size_t _queSize;
    std::queue<int> _que;
    std::mutex _mutex;
    std::condition_variable _notFull;
    std::condition_variable _notEmpty;
};


#endif