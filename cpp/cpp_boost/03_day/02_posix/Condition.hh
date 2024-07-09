#ifndef _CONDITION_HH_
#define _CONDITION_HH_

#include <pthread.h>

class Condition{
public: 
    Condition() = default;
    ~Condition() = default;

    int init(const pthread_condattr_t * = nullptr);

    int wait(pthread_mutex_t *);

    int notify_one();

    int notify_all();

    int destroy();

private:
    pthread_cond_t _cond;
};

#endif