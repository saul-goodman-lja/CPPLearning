#ifndef __MYTASK_HH__
#define __MYTASK_HH__

#include "TcpConnection.hh"
#include "TcpServer.hh"

#include <string>

using std::string;

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con);
    void process();
private:
    string _msg;
    TcpConnectionPtr _con;
};

#endif