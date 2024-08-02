#ifndef __TIMERTASK_H_
#define __TIMERTASK_H_

class TimerTask {
public:
    virtual void process() = 0;
    virtual ~TimerTask() = default;
};

#endif