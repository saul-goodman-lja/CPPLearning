#ifndef __REDISSERVER_HH__
#define __REDISSERVER_HH__

#include <hiredis/hiredis.h>
#include <string>
#include <pthread.h>

using std::string;

class RedisServer {
public:
    static RedisServer * createInstance();
    bool getKeyStatus(const string& key); // 是否存在key
    string getValue(const string& key); // 获取key 对应的value
    void setValue(const string& key, const string& value); // 设置KV
private:
    RedisServer(); // 连接
    ~RedisServer(); // 断开 释放资源
    RedisServer(const RedisServer&) = delete;
    RedisServer & operator=(const RedisServer&) = delete;
    static void init_r();
    static void destroy();
private:
    redisContext * _context;
    static RedisServer * _instance;
    static pthread_once_t _once;
};

#endif