#pragma once
#include "RpcService.h"
#include "ThreadPool.h"

const string registryIP = "127.0.0.1";
const int registryPort = 12345;

class RpcServer
{
private:
    string IP = "0.0.0.0";
    int port;
    ThreadPool *pool;
    string ServiceName;
    bool startParaOK ;
private:
    //检查启动参数
    bool checkStartPara(int argc, char const *argv[]);
    //向注册中心注册
    void registerService();
public:
    RpcServer(){pool = new ThreadPool(10,15);}
    RpcServer(int argc, char const *argv[],string serviceName);
    ~RpcServer();
    
    //设置服务名称
    void setServiceName(string ServiceName){this->ServiceName = ServiceName;}
    //添加方法
    void addMethod(string MethodName,RpcMethod method);
    //服务器开始运行
    void start();
};

//处理用户的连接
void handle(int sockcon,int load);

class RpcClient
{
private:
    string Targetip;
    int TargetPort;
    map<string, ServiceInfo> services;
    bool isRegistry;
private:
    bool checkStartPara(int argc, char const *argv[]);

public:
    RpcClient(){};
    RpcClient(int argc, char const *argv[]);
    ~RpcClient(){};
    //服务调用
    vector<string> rpcCall(string MethodName, initializer_list<string> Para);
    //服务发现
    void ServiceFind();
};
