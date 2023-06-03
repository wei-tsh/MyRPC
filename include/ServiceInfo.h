#include<string>
#include<map>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

struct ServiceInfo
{
    string ip;             // 服务IP地址
    int port;                   // 服务端口
    int load;                   // 服务负载
};

struct RegMes
{
    int type;
    string ServiceName;
    ServiceInfo info;
};

string sendServiceList(map<string,ServiceInfo> services);
map<string,ServiceInfo> getServiceList(string list);
string encodeRegMes(int type,string ServiceName,ServiceInfo info);
RegMes decodeRegMes(string Mes);