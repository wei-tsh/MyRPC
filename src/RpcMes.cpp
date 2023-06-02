#include "RpcMes.h"
using namespace rapidjson;

RpcMessage createRpcMessage(string ServiceName,string MethodName, int ParaCount, initializer_list<string> Para)
{
    RpcMessage a;
    a.parameterCount = ParaCount;
    a.serviceName = ServiceName;
    a.methodName = MethodName;
    for (auto i = Para.begin(); i != Para.end(); ++i)
    {
        a.parameters.push_back(*i);
    }

    return RpcMessage();
}

string encode(const RpcMessage &Mes)
{
    Document doc;
    doc.SetObject();
    doc.AddMember("ServiceName",Value(Mes.serviceName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("MethodName",Value(Mes.methodName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("ParameterCount",Value().SetInt(Mes.parameterCount).Move(),doc.GetAllocator());
    doc.AddMember("RetValCount",Value().SetInt(Mes.retvalCount).Move(),doc.GetAllocator());

    Value valArray(kArrayType);
    for (auto &i : Mes.returnValue){
        valArray.PushBack(Value(i.c_str(), doc.GetAllocator()), doc.GetAllocator());
    }
    doc.AddMember("Parameters",valArray.Move(),doc.GetAllocator());

    Value val2Array(kArrayType);
    for (auto &i : Mes.returnValue)
    {
        val2Array.PushBack(Value(i.c_str(), doc.GetAllocator()), doc.GetAllocator());
    }
    doc.AddMember("ReturnValues",valArray.Move(),doc.GetAllocator());
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

RpcMessage decode(const std::string& information)
{
    RpcMessage RecMes;
    Document doc;
    if(!doc.Parse(information.c_str()).HasParseError()){

        RecMes.serviceName = doc["ServiceName"].GetString();
        RecMes.methodName = doc["MethodName"].GetString();
        RecMes.parameterCount = doc["ParameterCount"].GetInt();
        RecMes.retvalCount = doc["RetValCount"].GetInt();

        const Value& a =doc["Parameters"];
        for (SizeType i = 0; i < RecMes.parameterCount; i++) {
                RecMes.parameters.push_back(a[i].GetString());
            }
        const Value& b =doc["ReturnValues"];
        for (SizeType i = 0; i < RecMes.retvalCount; i++) {
                RecMes.parameters.push_back(b[i].GetString());
            }
    }
    
    return RecMes;
}
    