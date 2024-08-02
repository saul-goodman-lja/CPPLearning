
#include "../../include/online/MyTask.hh"
#include "../../include/online/ProtocolParser.hh"
#include "../../include/online/Configuration.hh"
#include "../../include/online/KeyRecommander.hh"
#include "../../include/online/WebPageSearcher.hh"

#include <iostream>
MyTask::MyTask(const string &msg, const TcpConnectionPtr &con)
: _msg(msg)
, _con(con){}

void MyTask::process(){
    //业务逻辑的处理
    ProtocolParser parser(_msg);
    string req_type = parser.req_type();
    string req_content = parser.req_content();
    if(req_type == "suggest"){  // 关键词推荐业务
        KeyRecommander recommander(req_content, _con);
        recommander.execute();
    }else if(req_type == "search"){ // 网页搜索业务
        WebPageSearcher searcher(req_content, _con);
        searcher.execute();
    }else{
        std::cerr << "request error" << "\n";
        _msg = "request error";
        _con->sendInLoop(_msg);
    }
}