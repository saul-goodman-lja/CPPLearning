#include "TcpConnection.hh"
#include "Acceptor.hh"
#include "EventLoop.hh"
#include <iostream>
#include <string>

//连接建立
void onNewConnection(const TcpConnectionPtr &con){
    std::cout << con->toString() << " has connected!!!" << std::endl;
}

//消息到达
void onMessage(const TcpConnectionPtr &con){
    std::string msg = con->receive();
    std::cout << ">>>>recv from client : " << msg << std::endl;
    //接收到数据之后，可以进行业务逻辑的处理
    //处理完成之后，将其发送给客户端

    con->send(msg);
}

//连接断开
void onClose(const TcpConnectionPtr &con){
    std::cout << con->toString() << " has closed!!!" << std::endl;
}
auto test()-> void{    
    Acceptor acceptor("172.27.84.98", 8080);
    acceptor.ready();//此时处于监听状态

    EventLoop loop(acceptor);
    loop.setNewConnectionCallback(std::move(onNewConnection));
    loop.setMessageCallback(std::move(onMessage));
    loop.setCloseCallback(std::move(onClose));
    loop.loop();
}

auto main(void)-> int{
    test();
    return 0;
}