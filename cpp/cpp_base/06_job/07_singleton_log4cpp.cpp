#include <iostream>
#include <string>
#include <sstream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PropertyConfigurator.hh>

#define TransInfo(_info){ \
    std::ostringstream oss; \
    oss << __FILE__ << " " << __func__ << " " << __LINE__ << " " << _info; \
    msg = oss.str(); \
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

using namespace log4cpp;
using std::string;

class MyLogger{
public:

    static MyLogger * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new MyLogger();
        }
        return _pInstance;
    } 

    void warn(const char *msg);
    void error(const char *msg);
    void debug(const char *msg);
    void info(const char *msg);

    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

private:
    MyLogger(const string & initFileName = "log4cpp.properties");
    ~MyLogger();
    MyLogger(const MyLogger & rhs) = delete;
    MyLogger & operator=(const MyLogger & rhs) = delete;

    Category &myLog;
    static MyLogger *_pInstance;
};

MyLogger * MyLogger::_pInstance = nullptr;

MyLogger::MyLogger(const string & initFileName)
    : myLog(Category::getInstance("myLogger")){
    // auto ptn = new PatternLayout();
    // ptn->setConversionPattern("'%d' %c [%p] %m%n");

    // auto roll = new RollingFileAppender("rollingfile", filename, 5 * 1024, 9);
    // roll->setLayout(ptn);

    // myLog.setPriority(logLevel);
    // myLog.addAppender(roll);
    PropertyConfigurator::configure(initFileName);
}

MyLogger::~MyLogger(){
    Category::shutdown();
}

void MyLogger::warn(const char *msg){
    myLog.warn(msg);
}

void MyLogger::error(const char *msg){
    myLog.error(msg);
}

void MyLogger::debug(const char *msg){
    myLog.debug(msg);
}

void MyLogger::info(const char *msg){
    myLog.info(msg);
}

int main(void){
    for(int i = 0; i < 50; i++){
        LogInfo("The log is info message");
        LogError("The log is error message");
        LogWarn("The log is warn message");
        LogDebug("The log is debug message");
    }

    MyLogger::destroy();
}