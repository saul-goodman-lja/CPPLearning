#ifndef _MUTEX_LOCK_GURAD_HH_
#define _MUTEX_LOCK_GURAD_HH_

#include <pthread.h>

class MutexLockGurad{
public:
    MutexLockGurad(const pthread_mutex_t &);
    ~MutexLockGurad();
private:
    pthread_mutex_t _mutex;
};

#endif