#include"RpcMes.h"
#include"ServiceInfo.h"
#include<functional>
#include<iostream>
#include"TCP.h"

using RpcMethod = function<vector<string>(vector<string>)>;

// RPC服务类
class RpcService {
public:
    RpcService(){};
    RpcService(string ServiceName,string ip,int host);
    ~RpcService(){};

    string getServiceName(){return ServiceName;}
    string getIp(){return ip;}
    int getPort(){return port;}

    // 注册RPC方法
    void registerMethod(string methodName, RpcMethod method); 
        
    // 执行RPC方法
    vector<string> executeMethod(const RpcMessage& Mes);
private:
    map<string, RpcMethod> m_methods;  // 所有RPC方法的名称和函数指针
    string ServiceName;
    string ip;
    int port;
};

void registerService(RpcService service,string ip,int host);