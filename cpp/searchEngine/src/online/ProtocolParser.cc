#include "../../include/online/ProtocolParser.hh"
    
ProtocolParser::ProtocolParser(const std::string & req)
: _request(req){}
ProtocolParser::~ProtocolParser() = default;
std::string ProtocolParser::req_type(){
    return _request.substr(0, _request.find("/"));
}
std::string ProtocolParser::req_content(){
    return _request.substr(_request.find("/") + 1);
}