#include "../../include/online/TimerManager.hh"
#include "../../include/online/Configuration.hh"
#include "../../include/online/LogSingleTon.hh"

#include <poll.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <iostream>
#include <algorithm>
#include <sstream>

using std::ostringstream;
using std::cerr;

TimerManager::TimerManager()
: _timerfd(createTimerFd()) 
, _isStarted(false){}

TimerManager::~TimerManager()
{
    setTimerFd(0, 0);
    close(_timerfd);
}

void TimerManager::start(){
    struct pollfd pfd;
    pfd.fd = _timerfd;
    pfd.events = POLLIN;

    //设定定时器
    setTimerFd(
    std::stoi(Configuration::getInstance().getparameter("initSec")),
    std::stoi(Configuration::getInstance().getparameter("peridocSec")));
  
    ostringstream oss;
    oss << "timer起始时间: " << Configuration::getInstance().getparameter("initSec") << ", 周期: " << Configuration::getInstance().getparameter("peridocSec");
    LogInfo(oss.str());

    _isStarted = true;
    while(_isStarted)
    {
        int nready = poll(&pfd, 1, -1);
        if(-1 == nready && errno == EINTR)
        {
            continue;
        }
        else if(-1 == nready)
        {
            cerr << "-1 == nready" << "\n";
            return;
        }
        else if(0 == nready)
        {
            std::cout << ">>poll time_out!!!" << "\n";
        }
        else 
        {
            if(pfd.revents & POLLIN)
            {   
                handleRead();
                for(size_t idx = 0; idx < _wheelList.size(); idx++){
                    _wheelList[idx]->process();
                }
                std::cout << ">>timer!!!" << "\n";
            }
        }
    }
}
void TimerManager::stop(){
    if(_isStarted)
    {
        _isStarted = false;
        setTimerFd(0, 0);
    }
}
void TimerManager::attach(TimerTask *task){
    _wheelList.push_back(task);
}
void TimerManager::detach(TimerTask *task){
    auto it = std::remove(_wheelList.begin(), _wheelList.end(), task);
    _wheelList.erase(it, _wheelList.end());
}

//封装了read函数
void TimerManager::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_timerfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t))
    {
        perror("handleRead");
        return;
    }
}

//创建用于超时的文件描述符
int TimerManager::createTimerFd(){
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if(fd < 0)
    {
        ::perror("createTimerFd");
        return -1;
    }
    return fd;
}
//设置定时器（封装timerfd_settime)
void TimerManager::setTimerFd(int initSec, int peridocSec){
    struct itimerspec newValue;
    newValue.it_value.tv_sec = initSec;//起始时间
    newValue.it_value.tv_nsec = 0;

    newValue.it_interval.tv_sec = peridocSec;//周期时间
    newValue.it_interval.tv_nsec = 0;

    int ret = timerfd_settime(_timerfd, 0, &newValue, nullptr);
    if(ret < 0)
    {
        ::perror("setTimerFd");
        return;
    }
}