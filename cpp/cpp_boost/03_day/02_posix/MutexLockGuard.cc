#include "MutexLockGurad.hh"

#include <pthread.h>
#include <iostream>

MutexLockGurad::MutexLockGurad(const pthread_mutex_t &mutex)
: _mutex(mutex){
    pthread_mutex_lock(&_mutex);
}

MutexLockGurad::~MutexLockGurad(){
    pthread_mutex_unlock(&_mutex);
}
