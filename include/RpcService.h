#include"RpcMes.h"
#include"ServiceInfo.h"
#include<functional>
#include<iostream>
#include"TCP.h"

using RpcMethod = function<vector<string>(vector<string>)>;

// RPC服务类
class RpcService {
public:
    //构造函数
    RpcService(){};
    RpcService(string ServiceName,string ip,int host);
    //析构函数
    ~RpcService(){};

    //获取服务名称
    string getServiceName(){return ServiceName;}    
    //获得监听IP
    string getIp(){return ip;}
    //获得监听端口
    int getPort(){return port;}

    // 注册RPC方法
    void registerMethod(string methodName, RpcMethod method); 
        
    // 执行RPC方法
    vector<string> executeMethod(const RpcMessage& Mes);
private:
    map<string, RpcMethod> m_methods;   // 所有RPC方法的名称和函数指针
    string ServiceName;                 //服务名称
    string ip;                          //服务所在ip地址
    int port;                           //服务监听的端口
};

//向注册中心注册服务，输入参数为注册中心端口与ip
void registerService(RpcService service,string ip,int host);