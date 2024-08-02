#ifndef __WEB_PAGE_SEARCHER_HH__
#define __WEB_PAGE_SEARCHER_HH__

#include <string>
#include "TcpServer.hh"
#include "TcpConnection.hh"
#include <mutex>
#include <thread>

using std::string;

class WebPageSearcher {
public:
    WebPageSearcher(const string &, TcpConnectionPtr &);
    ~WebPageSearcher();
    void execute();
private:
    string _sought;
    TcpConnectionPtr _conn;
    std::mutex _redis_mutex;
};

#endif