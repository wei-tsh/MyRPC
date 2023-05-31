#pragma once

#include<string>
#include<map>
#include<mutex>
#include<vector>
#include<iostream>
#include "ServiceMes.h"

using namespace std;

struct ServiceInfo
{
    string ip;             // 服务IP地址
    int port;              // 服务端口
    int load;              // 服务负载
};

class RegistryCenter{
    public:
        RegistryCenter(){};
        ~RegistryCenter(){};

        // 注册服务
        void RegisterService(const string& ServiceName,const string& ip,int port);
        // 查询服务
        ServiceInfo FindService(const string& ServiceName);
        // 更新服务负载
        void UpdateLoad(const string& ServiceName,const string& ip,int load);

    private:
        map<string,vector<ServiceInfo> > services;   // 所有服务的名称和信息
        mutex m_mutex;                               // 锁，保护服务列表
};