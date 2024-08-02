#ifndef __PROTOCOL_PARSER_HH__
#define __PROTOCOL_PARSER_HH__
#include <string>

class ProtocolParser{
public:
    ProtocolParser(const std::string &);
    ~ProtocolParser();
    std::string req_type(); // 解析请求类型
    std::string req_content(); // 解析请求内容
private:
    std::string _request;
};

#endif