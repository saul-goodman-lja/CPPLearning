#include "../../include/online/WebPageSearcher.hh"
#include "../../include/online/WebPageQuery.hh"
#include "../../include/online/RedisServer.hh"
#include <hiredis/hiredis.h>

#include <iostream>
WebPageSearcher::WebPageSearcher(const string & sought, TcpConnectionPtr &conn)
: _sought(sought), _conn(conn){}
WebPageSearcher::~WebPageSearcher() = default;
void WebPageSearcher::execute(){

    if(_sought.empty()){
        _conn->sendInLoop("");
        return;
    }

    {   
        std::lock_guard<std::mutex> lock(_redis_mutex);
        if(RedisServer::createInstance()->getKeyStatus(_sought)){
            std::cout << "搜索内容: " << _sought << " ---成功命中Redis ." << "\n";
            _conn->sendInLoop(RedisServer::createInstance()->getValue(_sought));
            return;
        }else{
            std::cout << "搜索内容: " << _sought << " ---未命中Redis ." << "\n";
        }
    }

    // TODO 缓存
    WebPageQuery query;
    string result = query.doQuery(_sought);
    if(result == "no result"){
        _conn->sendInLoop("");
        return;
    }
    _conn->sendInLoop(result);
    
    {
        std::lock_guard<std::mutex> lock(_redis_mutex);
        RedisServer::createInstance()->setValue(_sought, result);
        std::cout << _sought << " 已成功存入Redis ." << "\n";
    }
}