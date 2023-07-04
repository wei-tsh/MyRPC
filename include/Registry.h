#pragma once

#include<mutex>
#include<vector>
#include<iostream>
#include "TCP.h"
#include "ServiceInfo.h"
#include<thread>
#include"RpcMes.h"

//注册中心
class RegistryCenter{
    public:
        //构造函数
        RegistryCenter();
        //析构函数
        ~RegistryCenter(){};

        // 注册服务
        void RegisterService(const string& ServiceName,const string& ip,int port);
        // 查询服务
        string FindService();
        // 心跳检测
        static void heartCheck(RegistryCenter* center);
        
    private:
        //删除服务
        void DeleteService(string ServiceName);
        // 更新服务负载
        void UpdateLoad(const string& ServiceName,int load);
    private:
        map<string,ServiceInfo> services;            // 所有服务的名称和信息
        thread HeartCheck;                           // 用于心跳检测的线程
        mutex m_mutex;                               // 锁，保护服务列表
};

//服务中心启动参数
bool checkStartPara(int argc, char const *argv[],string &ip,int &port);

//预期实现功能
//更新服务负载，心跳检测