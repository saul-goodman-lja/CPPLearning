#ifndef __KEY_RECOMMANDER_HH__
#define __KEY_RECOMMANDER_HH__

#include "TcpServer.hh"
#include <string>
#include <sstream>

using std::ostringstream;
using std::string;

class KeyRecommander
{
  public:
    KeyRecommander(const string& query, const TcpConnectionPtr&);
    ~KeyRecommander();
    string doQuery();
    void execute();

  private:
    size_t nBytesCode(const char ch);
    std::size_t length(const std::string& str);
    int triple_min(const int& a, const int& b, const int& c);
    int editDistance(const string& lhs, const string& rhs);
    void ProgressCache(string &, ostringstream &);
    void TimerManagerCache(string &, ostringstream &);
    void DoubleCache(string &, ostringstream &);
  private:
    string _queryWord;
    TcpConnectionPtr _conn;
};

#endif