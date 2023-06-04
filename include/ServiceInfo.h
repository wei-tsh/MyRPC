#include<string>
#include<map>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

//服务信息
struct ServiceInfo
{
    string ip;             // 服务IP地址
    int port;                   // 服务端口
    int load;                   // 服务负载
};

//向注册中心发送的信息
struct RegMes
{
    int type;
    string ServiceName;
    ServiceInfo info;
};

//将服务表序列化转化成json
string sendServiceList(map<string,ServiceInfo> services);
//将json文件反序列化成服务表
map<string,ServiceInfo> getServiceList(string list);

//将注册信息序列化转化成json
string encodeRegMes(int type,string ServiceName,ServiceInfo info);
//将json反序列化成注册信息
RegMes decodeRegMes(string Mes);