#pragma once

#include <iostream>
#include "TCP.h"
#include "RpcMes.h"
#include "ServiceInfo.h"

//服务调用
vector<string> rpcCall(map<string, ServiceInfo> Services,string MethodName, initializer_list<string> Para);
//服务发现
map<string,ServiceInfo> ServiceFind(const string ip, int port);