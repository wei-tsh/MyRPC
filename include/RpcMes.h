#include<string>

struct RpcMessageHeader
{
    std::string serviceName;  // 服务名称
    std::string methodName;   // 方法名称    
    int parameterCount;       // 参数个数
};