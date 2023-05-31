#pragma once

#include<string>
#include<vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

//

struct RpcMessage
{
    string serviceName;  // 服务名称
    int parameterCount;       // 参数个数
    vector<string> parameters; // 参数列表
    string returnValue;             // 返回值
};

RpcMessage createRpcMessage(string ServiceName,int ParaCount, initializer_list<string> Para);
string encode(const RpcMessage& Mes);
RpcMessage decode(const string& information);