#include "../../include/online/LogSingleTon.hh"
#include "../../include/online/Configuration.hh"
MyLogger * MyLogger::getInstance(){
    pthread_once(&_once,init_r);
    return _instance;
}

void MyLogger::init_r(){
    _instance = new MyLogger();
    atexit(destroy);
}

void MyLogger::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}

MyLogger::MyLogger()
: _myLog(log4cpp::Category::getInstance("myLogger"))
{
    log4cpp::PropertyConfigurator::configure(Configuration::getInstance().getparameter("log4cpp"));
}
MyLogger::~MyLogger(){
    log4cpp::Category::shutdown();
}
void MyLogger::warn(const char *msg){
    _myLog.warn(msg);
}

void MyLogger::error(const char *msg){
    _myLog.error(msg);
}

void MyLogger::debug(const char *msg){
    _myLog.debug(msg);
}

void MyLogger::info(const char *msg){
    _myLog.info(msg);
}


MyLogger *MyLogger::_instance = nullptr;
pthread_once_t MyLogger::_once = PTHREAD_ONCE_INIT;