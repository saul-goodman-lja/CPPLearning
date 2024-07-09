#ifndef _TCPCONNECTION_HH_
#define _TCPCONNECTION_HH_

#include "SocketIO.hh"
#include "Socket.hh"
#include "InetAddress.hh"

#include <memory>
#include <functional>

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string & msg);
    string receive();
    bool isClosed() const;

    //为了方便调试的函数
    string toString();
private:
    //获取本端地址与对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

public:
    //三个回调的注册
    void setNewConnectionCallback(const TcpConnectionCallback &cb);
    void setMessageCallback(const TcpConnectionCallback &cb);
    void setCloseCallback(const TcpConnectionCallback &cb);

    //三个回调的执行
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
private:
    SocketIO _sockIO;

    //为了调试而加入的三个数据成员
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    //添加三个数据成员，对应的就是三个事件 
    TcpConnectionCallback _onNewConnectionCb; //连接建立
    TcpConnectionCallback _onMessageCb; //消息到达（文件描述符可读）
    TcpConnectionCallback _onCloseCb; //连接建立
};

#endif