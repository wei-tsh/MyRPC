#pragma once
#include "RpcService.h"
#include "ThreadPool.h"



class RpcServer
{
private:
    string Regip;
    int RegPort;
    string IP;
    int port;
    ThreadPool *pool;
public:
    RpcServer(){pool = new ThreadPool(10,15);}
    RpcServer(string ip,int port,string regip,int regport);
    ~RpcServer(){pool->~ThreadPool();}
    
    //向服务器维护的map添加服务
    void addService(string ServiceName);
    //添加方法
    void addMethod(string ServiceName,string MethodName,RpcMethod method);
    void registerService();
    //服务器开始运行
    void start();
};

//处理用户的连接
void handle(int sockcon);

class RpcClient
{
private:
    string Regip;
    int RegPort;
    map<string, ServiceInfo> services;
public:
    RpcClient(){};
    RpcClient(string regip,int regport);
    ~RpcClient(){};
    //服务调用
    vector<string> rpcCall(string MethodName, initializer_list<string> Para);
    //服务发现
    void ServiceFind();
};
