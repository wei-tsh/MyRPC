#pragma once

#include"RpcMes.h"
#include"ServiceInfo.h"
#include<functional>
#include<iostream>
#include"TCP.h"

using RpcMethod = function<string(vector<string>&,vector<string>&)>;

// RPC服务类
class RpcService {
public:
    //构造函数
    RpcService(){};
    //析构函数
    ~RpcService(){};

    //获取服务名称
    string getServiceName(){return ServiceName;}    

    // 注册RPC方法
    void registerMethod(string methodName, RpcMethod method); 
        
    // 执行RPC方法
    string executeMethod(RpcMessage& Mes);
private:
    map<string, RpcMethod> m_methods;   // 所有RPC方法的名称和函数指针
    string ServiceName;                 //服务名称
};
