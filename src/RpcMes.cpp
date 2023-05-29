#include "RpcMes.h"
using namespace rapidjson;

std::string encode(const RpcMessage& Mes)
{
    Document doc;
    doc.SetObject();
    doc.AddMember("ServiceName",Value(Mes.serviceName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("MethodName",Value(Mes.methodName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("ParameterCount",Value().SetInt(Mes.parameterCount).Move(),doc.GetAllocator());

    Value valArray(kArrayType);
    for (int i = 0; i < Mes.parameterCount; i++){
        std::string str = Mes.parameters[i];
        Value user(kObjectType);
        user.AddMember("parameter", Value(str.c_str(), doc.GetAllocator()), doc.GetAllocator());
        valArray.PushBack(user, doc.GetAllocator());

    }
    doc.AddMember("Parameters",valArray.Move(),doc.GetAllocator());
    doc.AddMember("ReturnValue",Value(Mes.returnValue.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());

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
        RecMes.methodName = doc["MethodName"].GetString();
        RecMes.serviceName = doc["ServiceName"].GetString();
        RecMes.parameterCount = doc["ParameterCount"].GetInt();
        const Value& a =doc["Parameters"];
        for (SizeType i = 0; i < RecMes.parameterCount; i++)
        {
            RecMes.parameters.push_back(a[i]["parameter"].GetString());
        }
        RecMes.returnValue = doc["ReturnValue"].GetString();
    }
    
    return RecMes;
}
    