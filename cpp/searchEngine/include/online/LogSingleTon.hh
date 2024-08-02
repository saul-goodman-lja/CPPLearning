#ifndef __LOG_SINGLETON_HH__
#define __LOG_SINGLETON_HH__

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <pthread.h>
#include <iostream>
#include <string>
#include <sstream>

using std::string;

#define TransInfo(_info){ \
    std::ostringstream ossInfo; \
    ossInfo << __FILE__ << " " << __func__ << " " << __LINE__ << " " << _info; \
    msg = ossInfo.str(); \
}

#define LogInfo(_info) \
    do{ \
        string msg; \
        TransInfo(_info); \
        MyLogger::getInstance()->info(msg.c_str()); \
    }while(0)

#define LogError(_info) \
    do{ \
        string msg; \
        TransInfo(_info); \
        MyLogger::getInstance()->info(msg.c_str()); \
    }while(0)

#define LogWarn(_info) \
    do{ \
        string msg; \
        TransInfo(_info); \
        MyLogger::getInstance()->info(msg.c_str()); \
    }while(0)

#define LogDebug(_info) \
    do{ \
        string msg; \
        TransInfo(_info); \
        MyLogger::getInstance()->info(msg.c_str()); \
    }while(0)

// 日志单例
class MyLogger{
public:
    static MyLogger * getInstance();
    void warn(const char *msg);
    void error(const char *msg); 
    void debug(const char *msg);
    void info(const char *msg);
private:
    MyLogger();
    ~MyLogger();
    MyLogger(const MyLogger & rhs) = delete;
    MyLogger & operator=(const MyLogger & rhs) = delete;
    static void init_r();
    static void destroy();
private:
    log4cpp::Category & _myLog;
    static MyLogger * _instance;
    static pthread_once_t _once;
};

#endif