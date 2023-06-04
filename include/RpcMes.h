#include<string>
#include<vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

//RPC协议报文
struct RpcMessage
{
    string methodName;                      //方法名称
    string serviceName;                     // 服务名称
    vector<string> parameters;              // 参数列表
    vector<string> returnValue;             // 返回值
};
//创建一个RPC报文
RpcMessage createRpcMessage(string ServiceName,string MethodName, initializer_list<string> para);
//序列化RPC报文
string encode(const RpcMessage& Mes);
//反序列化RPC报文
RpcMessage decode(const string& information);