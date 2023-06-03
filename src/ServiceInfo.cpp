#include "ServiceInfo.h"

using namespace rapidjson;

string sendServiceList(map<string, ServiceInfo> services)
{
    Document doc;
    doc.SetArray();
    for (auto &i : services)
    {
        Value valarray(kObjectType);
        valarray.AddMember("ServiceName",Value(i.first.c_str(),doc.GetAllocator()),doc.GetAllocator());
        valarray.AddMember("IP",Value(i.second.ip.c_str(),doc.GetAllocator()),doc.GetAllocator());
        valarray.AddMember("Port",Value().SetInt(i.second.port),doc.GetAllocator());
        valarray.AddMember("Load",Value().SetInt(i.second.load),doc.GetAllocator());
        doc.PushBack(valarray, doc.GetAllocator());
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

map<string, ServiceInfo> getServiceList(string list)
{
    map<string, ServiceInfo> Services;
    Document doc;

    if(!doc.Parse(list.c_str()).HasParseError()){
        for (Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr) {
            ServiceInfo serinfo;
            const Value& obj = *itr;
            serinfo.ip = obj["IP"].GetString();
            serinfo.port = obj["Port"].GetInt();
            serinfo.load = obj["Load"].GetInt();

            Services[obj["ServiceName"].GetString()] = serinfo;
        }
    }

    return Services;
}

string encodeRegMes(int type,string ServicName, ServiceInfo info)
{
    Document doc;
    doc.SetObject();

    doc.AddMember("Type",Value().SetInt(type),doc.GetAllocator());
    doc.AddMember("ServiceName",Value(ServicName.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("IP",Value(info.ip.c_str(),doc.GetAllocator()).Move(),doc.GetAllocator());
    doc.AddMember("Port",Value().SetInt(info.port).Move(),doc.GetAllocator());
    doc.AddMember("Load",Value().SetInt(info.load).Move(),doc.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}

RegMes decodeRegMes(string Mes)
{
    RegMes regmes;
    Document doc;

    if(!doc.Parse(Mes.c_str()).HasParseError()){
        regmes.type = doc["Type"].GetInt();
        regmes.ServiceName = doc["ServiceName"].GetString();
        regmes.info.ip = doc["IP"].GetString();
        regmes.info.port = doc["Port"].GetInt();
        regmes.info.load = doc["Load"].GetInt();
    }

    return regmes;
}
