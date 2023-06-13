#include "RpcMes.h"
using namespace rapidjson;

RpcMessage createRpcMessage(string ServiceName,string MethodName,initializer_list<string> Para)
{
    RpcMessage a;
    a.serviceName = ServiceName;
    a.methodName = MethodName;
    for (auto i = Para.begin(); i != Para.end(); ++i)
    {
        a.parameters.push_back(*i);
    }

    return a;
}

string encode(const RpcMessage &Mes)
{
    Document doc;
    doc.SetObject();
    doc.AddMember("ServiceName",Value(Mes.serviceName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("MethodName",Value(Mes.methodName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());

    Value valArray(kArrayType);
    for (auto &i : Mes.parameters){
        valArray.PushBack(Value(i.c_str(), doc.GetAllocator()), doc.GetAllocator());
    }
    doc.AddMember("Parameters",valArray.Move(),doc.GetAllocator());

    Value val2Array(kArrayType);
    for (auto &i : Mes.returnValue)
    {
        val2Array.PushBack(Value(i.c_str(), doc.GetAllocator()), doc.GetAllocator());
    }
    doc.AddMember("ReturnValues",val2Array.Move(),doc.GetAllocator());
    doc.AddMember("Error",Value(Mes.error.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());

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
        
        const Value& a =doc["Parameters"];
        if(a.IsArray()&&!a.Empty())
        {
            for (SizeType i = 0; i < a.Size(); i++) 
            {
                RecMes.parameters.push_back(a[i].GetString());
            }
        }
        
        const Value& b =doc["ReturnValues"];
        if(b.IsArray()&&!b.Empty())
        {
            for (SizeType i = 0; i < b.Size(); i++) 
            {
                RecMes.returnValue.push_back(b[i].GetString());
            }
        }

        RecMes.error = doc["Error"].GetString();
    }
    
    return RecMes;
}
    