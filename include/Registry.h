#pragma once

#include<mutex>
#include<vector>
#include<iostream>
#include "TCP.h"
#include "ServiceInfo.h"

//注册中心
class RegistryCenter{
    public:
        //构造函数
        RegistryCenter(){};
        //析构函数
        ~RegistryCenter(){};

        // 注册服务
        void RegisterService(const string& ServiceName,const string& ip,int port);
        // 查询服务
        string FindService();
        // 更新服务负载
        void UpdateLoad(const string& ServiceName,const string& ip,int load);

    private:
        map<string,ServiceInfo> services;            // 所有服务的名称和信息
        mutex m_mutex;                               // 锁，保护服务列表
};

//服务中心启动参数
bool checkStartPara(int argc, char const *argv[],string &ip,int &port);

//预期实现功能
//更新服务负载，心跳检测