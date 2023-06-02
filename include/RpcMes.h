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
    int parameterCount;                     // 参数个数
    int retvalCount;                        //返回值个数
    vector<string> parameters;              // 参数列表
    vector<string> returnValue;             // 返回值
};

RpcMessage createRpcMessage(string ServiceName,string MethodName,int ParaCount, initializer_list<string> para);
string encode(const RpcMessage& Mes);
RpcMessage decode(const string& information);