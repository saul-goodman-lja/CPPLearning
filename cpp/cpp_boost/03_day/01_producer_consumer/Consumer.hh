#ifndef _CONSUMER_HH_
#define _CONSUMER_HH_

#include "TaskQueue.hh"

class Consumer{
public:
    Consumer() = default;
    ~Consumer() = default;
    void consume(TaskQueue &);
};

#endif