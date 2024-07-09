#include "MutexLock.hh"
#include <pthread.h>
#include <memory>
MutexLock::MutexLock()
: lockGurad(nullptr){}

MutexLock::~MutexLock(){}

int MutexLock::init(const pthread_mutexattr_t *attr){
    return pthread_mutex_init(&_mutex, attr);
}

int MutexLock::lock(){
    if(nullptr == lockGurad){
        lockGurad = std::make_unique<MutexLockGurad>(_mutex);
        return 0;
    }
    return -1;
}

int MutexLock::trylock(){
    return pthread_mutex_trylock(&_mutex);
}
int MutexLock::unlock(){
    if(lockGurad){
        lockGurad.reset(nullptr);
        return 0;
    }
    return -1;
}

int MutexLock::destroy(){
    return pthread_mutex_destroy(&_mutex);
}