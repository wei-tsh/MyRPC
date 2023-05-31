#include "ServiceMes.h"
using namespace rapidjson;

string SerEncode(const ServiceMes &Mes)
{
    Document doc;
    doc.SetObject();
    doc.AddMember("ServiceName",Value(Mes.ServiceName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("Type",Value().SetInt(Mes.type).Move(),doc.GetAllocator());
    doc.AddMember("Load",Value().SetInt(Mes.load).Move(),doc.GetAllocator());
    doc.AddMember("IP",Value(Mes.ip.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("Port",Value().SetInt(Mes.port).Move(),doc.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

ServiceMes SerDecode(const string &information)
{
    ServiceMes SerMes;
    Document doc;
    if(!doc.Parse(information.c_str()).HasParseError()){
        SerMes.ServiceName = doc["ServiceName"].GetString();
        SerMes.type = doc["Type"].GetInt();
        SerMes.ip = doc["IP"].GetString();
        SerMes.port = doc["Port"].GetInt();
        SerMes.load = doc["Load"].GetInt();
    }
    
    return SerMes;
}
