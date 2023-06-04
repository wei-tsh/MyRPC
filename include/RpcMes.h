#include<string>
#include<vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

//

struct RpcMessage
{
    string methodName;                      //方法名称
    string serviceName;                     // 服务名称
    vector<string> parameters;              // 参数列表
    vector<string> returnValue;             // 返回值
};

RpcMessage createRpcMessage(string ServiceName,string MethodName, initializer_list<string> para);
string encode(const RpcMessage& Mes);
RpcMessage decode(const string& information);