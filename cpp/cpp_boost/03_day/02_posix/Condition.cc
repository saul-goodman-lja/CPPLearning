#include "Condition.hh"

int Condition::init(const pthread_condattr_t *attr){
    return pthread_cond_init(&_cond, attr);
}

int Condition::wait(pthread_mutex_t *pMutex){
    return pthread_cond_wait(&_cond, pMutex);
}

int Condition::notify_one(){
    return pthread_cond_signal(&_cond);
}

int Condition::notify_all(){
    return pthread_cond_broadcast(&_cond);
}

int Condition::destroy(){
    return pthread_cond_destroy(&_cond);
}