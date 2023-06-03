#pragma once

#include <iostream>
#include "TCP.h"
#include "RpcMes.h"
#include "ServiceInfo.h"

vector<string> rpcCall(map<string, ServiceInfo> Services,string MethodName, initializer_list<string> Para);
map<string,ServiceInfo> ServiceFind(const string ip, int port);