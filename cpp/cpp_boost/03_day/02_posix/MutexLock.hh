#ifndef _MUTEX_LOCK_HH_
#define _MUTEX_LOCK_HH_

#include "MutexLockGurad.hh"
#include <pthread.h>
#include <memory>

class MutexLock{
public:
    MutexLock();
    ~MutexLock();
    int init(const pthread_mutexattr_t * = nullptr);
    int lock();
    int trylock();
    int unlock();
    int destroy();
private:
    pthread_mutex_t _mutex;
    std::unique_ptr<MutexLockGurad> lockGurad;
};

#endif