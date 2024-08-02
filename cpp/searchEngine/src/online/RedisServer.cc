#include "../../include/online/RedisServer.hh"

#include <hiredis/hiredis.h>
#include <sstream>
#include <iostream>

using std::ostringstream;
RedisServer::RedisServer()
: _context(redisConnect("127.0.0.1", 6379)){}
RedisServer::~RedisServer(){
    redisFree(_context);
}

RedisServer * RedisServer::createInstance(){
    pthread_once(&_once,init_r);
    return _instance;
}
void RedisServer::init_r(){
    _instance = new RedisServer();
    atexit(destroy);
}
void RedisServer::destroy(){
    if(_instance){
        delete _instance;
        _instance = nullptr;
    }
}
bool RedisServer::getKeyStatus(const string& key){
    redisReply *reply = (redisReply*)redisCommand(_context,"EXISTS %s", key.c_str());
    bool rst = reply->integer == 1;
    std::cout << "key status: " << rst << std::endl;
    freeReplyObject(reply);
    return rst;
}
string RedisServer::getValue(const string& key){
    redisReply *reply = (redisReply*)redisCommand(_context,"GET %s", key.c_str());
    string rst = reply->str;
    freeReplyObject(reply);
    return rst;
}
void RedisServer::setValue(const string &key, const string &value){
    redisReply *reply = (redisReply*)redisCommand(_context,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}
RedisServer * RedisServer::_instance = nullptr;
pthread_once_t RedisServer::_once = PTHREAD_ONCE_INIT;

// int main(){
//     RedisServer *redis = RedisServer::createInstance();
//     redis->setValue("name","zhangsan");
//     std::cout << redis->getValue("name") << std::endl;
// }