#include<string>
#include<vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
//

struct RpcMessage
{
    std::string serviceName;  // 服务名称
    std::string methodName;   // 方法名称    
    int parameterCount;       // 参数个数
    std::vector<std::string> parameters; // 参数列表
    std::string returnValue;             // 返回值
};

std::string encode(const RpcMessage& Mes);
RpcMessage decode(const std::string& information);