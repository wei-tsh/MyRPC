#include "RpcMes.h"
using namespace rapidjson;

std::string encodeHeader(const RpcMessageHeader& header)
{
    Document doc;
    doc.SetObject();
    doc.AddMember("ServiceName",Value(header.serviceName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("MethodName",Value(header.methodName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("ParameterCount",Value().SetInt(header.parameterCount).Move(),doc.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

std::string encodeBody(const RpcMessageBody& body)
{
    Document doc;
    doc.SetObject();
    doc.AddMember("ReturnValue",Value(body.returnValue.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());

    Value valArray(kArrayType);
    for (int i = 0; i < body.parameters.size(); i++){
        std::string str = body.parameters[i];
        Value user(kObjectType);
        user.AddMember("parameter", Value(str.c_str(), doc.GetAllocator()), doc.GetAllocator());
        valArray.PushBack(user, doc.GetAllocator());

    }
    doc.AddMember("Parameters",valArray.Move(),doc.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

RpcMessageHeader decodeHeader(const std::string& header);
RpcMessageBody decodeBody(const std::string& body);