#include "../../include/offline/DictProducer.hh"
#include "../../include/offline/SplitToolCppPaddlePaddleLac.hh"
#include "../../include/offline/Configuration.hh"
int main(){
    Configuration config;
    SplitToolCppPaddlePaddleLac splitTool(config);
    DictProducer dictProducer("" ,&splitTool);
    dictProducer.buildEnDict();
    dictProducer.buildCnDict();
    dictProducer.createIndex();
    return 0;
}