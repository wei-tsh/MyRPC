#pragma once

#include <iostream>
#include "TCP.h"
#include "RpcMes.h"
#include "ServiceInfo.h"

//服务调用
vector<string> rpcCall(map<string, ServiceInfo> Services,string MethodName, initializer_list<string> Para);
//服务发现
map<string,ServiceInfo> ServiceFind(const string ip, int port);

//客户端启动参数
bool checkStartPara(int argc, char const *argv[],string &ip,int &port);