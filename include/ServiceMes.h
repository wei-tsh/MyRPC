#pragma once
#include<string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

struct ServiceMes
{
    int type;              //区分客户端、服务端
    string ServiceName;    //服务名称
    string ip;             // 服务IP地址
    int port;              // 服务端口
    int load;              //负载
};

string SerEncode(const ServiceMes& Mes);
ServiceMes SerDecode(const string& information);