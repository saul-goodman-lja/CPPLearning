#ifndef __TIMERMANAGER_HH__
#define __TIMERMANAGER_HH__

#include "TimerTask.hh"

#include <vector>

using std::vector;

class TimerManager{
public:
    TimerManager();
    ~TimerManager();
    void start();
    void stop();
    void attach(TimerTask *task); // attach task to timer manager
    void detach(TimerTask *task); // detach task from timer manager

private:
    //封装了read函数
    void handleRead();
    //创建用于超时的文件描述符
    int createTimerFd();
    //设置定时器（封装timerfd_settime)
    void setTimerFd(int initSec, int peridocSec);
private:
    int _timerfd;
    vector<TimerTask *> _wheelList;
    bool _isStarted;
};

#endif