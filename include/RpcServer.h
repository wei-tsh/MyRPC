#include<map>
#include<string>
#include<iostream>
#include<vector>
#include"RpcMes.h"
#include"ServiceInfo.h"
#include<functional>
#include"TCP.h"

using namespace std;
using RpcMethod = function<vector<string>(vector<string>)>;

// RPC服务类
class RpcService {
public:
    RpcService(string ServiceName,string ip,int host);
    ~RpcService(){};

    string getServiceName(){return ServiceName;}

    void registerService();

    void setRegistryAddress(string ip,int host);

    // 注册RPC方法
    void registerMethod(string& methodName, RpcMethod method); 
        
    // 执行RPC方法
    vector<string> executeMethod(const RpcMessage& Mes);
private:
    map<string, RpcMethod> m_methods;  // 所有RPC方法的名称和函数指针
    string ServiceName;
    string ip;
    int port;
    string registry_ip;
    int registry_host;
};