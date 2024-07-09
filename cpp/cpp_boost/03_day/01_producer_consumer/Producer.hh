#ifndef _PRODUCTER_HH_
#define _PRODUCTER_HH_
#include "TaskQueue.hh"
class Producter{
public:
    Producter() = default;
    ~Producter() = default;
    void produce(TaskQueue &);
};

#endif