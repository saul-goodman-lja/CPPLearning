#ifndef _EVENTLOOP_HH_
#define _EVENTLOOP_HH_
#include <my_header.h>
#include "Acceptor.hh"
#include "TcpConnection.hh"

#include <vector>
#include <memory>
#include <map>
#include <functional>

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;

class EventLoop{
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    //循环与非循环
    void loop();
    void unloop();

    //封装epoll_wait的函数
    void waitEpollFd();

    //处理新的连接
    void handleNewConnection();

    //处理老的连接上的数据的收发
    void handleMessage(int);

    //封装epoll_create函数
    int createEpollFd();

    //将文件描述符放在红黑树上进行监听
    void addEpollReadFd(int);

    //将文件描述符从红黑树上取消监听
    void delEpollReadFd(int);

    //三个回调的注册
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);

private:
    int _epfd; //是epoll_create创建出来的文件描述符
    std::vector<struct epoll_event> _evtList; //存放满足条件的文件描述符的数据结构
    bool _isLooping; //标识循环运行与否
    Acceptor &_acceptor; //连接器Acceptor的引用
    std::map<int, std::shared_ptr<TcpConnection>> _conns; //存放文件描述符与TcpConnection的键值对

    //添加三个数据成员，对应的就是三个事件
    TcpConnectionCallback _onNewConnectionCb; //连接建立
    TcpConnectionCallback _onCloseCb; //连接建立
    TcpConnectionCallback _onMessageCb;//消息到达（文件描述符可读）
};

#endif