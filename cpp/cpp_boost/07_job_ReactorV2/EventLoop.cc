#include "errno.h"
#include "EventLoop.hh"
#include <iostream>
EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtList(1024)
, _isLooping(false)
, _acceptor(acceptor)
{
    //获取listenfd（也就是socket返回的文件描述符）
    //并且将listenfd放在红黑树上进行监听
    int listenfd = _acceptor.fd();
    addEpollReadFd(listenfd);
}

EventLoop::~EventLoop(){
    ::close(_epfd);
}

//循环与非循环
void EventLoop::loop(){
    _isLooping = true;
    while (_isLooping) {
        waitEpollFd();
    }
}

void EventLoop::unloop(){
    _isLooping = false;
}

//封装epoll_wait的函数
void EventLoop::waitEpollFd(){
    int nready = 0;
    do{
        nready = ::epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    }while(nready == -1 && errno == EINTR);

    if(nready == -1){
        ::perror("epollwait, nready == -1");
        return;
    }
    if(nready == 0){
        std::cout << ">> epoll_wait timeout!!!" << std::endl;
    }else{
        //考虑一个问题，vector有可能越界的问题，需要手动扩容
        //nready == -1(int--->size_t)
        //for(size_t idx = 99; idx > 0; idx -=2)
        //{
        //
        //}

        if(static_cast<int>(_evtList.size()) == nready){
            _evtList.resize(2 * _evtList.size());
        }

        for(int idx = 0; idx < nready; idx++){
            int cfd = _evtList[idx].data.fd;
            int listenfd = _acceptor.fd();
            if(cfd == listenfd){
                //有新的连接请求上来
                handleNewConnection();
            }else{
                //处理老的连接
                handleMessage(cfd);
            }
        }
    }
}

//处理新的连接
void EventLoop::handleNewConnection(){
    //调用Acceptor的accept函数，如果该函数的返回值
    //connfd是正常值，就表明三次握手建立成功了
    int connfd = _acceptor.accept();
    if(connfd < 0){
        ::perror("handleNewConnection");
        return;
    }
    //监听connfd
    addEpollReadFd(connfd);
    
    //创建出TcpConnection的对象
    /* TcpConnection con(connfd); */
    TcpConnectionPtr con(new TcpConnection(connfd));

    //当连接TcpConnection对象创建出来之后，需要将三个回调
    //从EventLoop中传递给TcpConnection的对象
    con->setNewConnectionCallback(_onNewConnectionCb); //连接建立
    con->setMessageCallback(_onMessageCb); //消息达到
    con->setCloseCallback(_onCloseCb); //连接断开

    //将connfd与TcpConnection的键值对存放在map中
    /* _conns.insert(std::make_pair(connfd, con)); */
    _conns[connfd] = con;

    //连接建立的事件的触发时机已经到达了，可以执行
    con->handleNewConnectionCallback();
}

//处理老的连接上的数据的收发
void EventLoop::handleMessage(int fd){
    if(_conns.count(fd)){
        //拿到这个连接之后，如何判断连接是不是断开的呢
        //如果连接断开就可以执行连接断开的事件
        //否则就执行消息到达的事件
        bool flag = _conns[fd]->isClosed();
        if(flag){
            //连接断开
            _conns[fd]->handleCloseCallback(); //连接断开的事件的触发时机
            //将fd从红黑树上删除
            delEpollReadFd(fd);
            //还需要将连接从map中删除
            _conns.erase(fd);
        }else{
            //连接没有断开，可以正常收发数据
            _conns[fd]->handleMessageCallback(); //消息到达
        }
    }else{
        std::cout << "该连接不存在" << std::endl;
        return;
    }
}

//封装epoll_create函数
int EventLoop::createEpollFd(){
    int fd = epoll_create(1);
    if(fd < 0){
        ::perror("epoll_create");
        return -1;
    }
    return fd;
}

//将文件描述符放在红黑树上进行监听
void EventLoop::addEpollReadFd(int fd){
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(ret < 0){
        ::perror("addEpollReadFd");
        return ;
    }
}

//将文件描述符从红黑树上取消监听
void EventLoop::delEpollReadFd(int fd){
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0){
        ::perror("delEpollReadFd");
        return ;
    }
}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb){
    _onNewConnectionCb = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback &&cb){
    _onMessageCb = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb){
    _onCloseCb = std::move(cb);
}