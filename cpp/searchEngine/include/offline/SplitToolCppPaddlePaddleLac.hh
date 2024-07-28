#ifndef __SPLITTOOLCPPPADDLEPADDLELAC_HH__
#define __SPLITTOOLCPPPADDLEPADDLELAC_HH__

#include "Configuration.hh"
#include "SplitTool.hh"

class SplitToolCppPaddlePaddleLac 
: public SplitTool
{
public: 
    SplitToolCppPaddlePaddleLac(Configuration &conf);
    virtual ~SplitToolCppPaddlePaddleLac();
    virtual vector<string> cut(const string &) override;
private:
    Configuration &_conf;
};

#endif