#pragma once

#include <iostream>
#include "TCP.h"
#include "RpcMes.h"
#include "ServiceInfo.h"

using namespace std;

vector<string> rpcCall(const string ip, int port, string ServiceName,string MethodName,int ParaCount, initializer_list<string> Para);
map<string,ServiceInfo> ServiceFind(const string ip, int port);