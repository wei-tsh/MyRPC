#include "Registry.h"

void RegistryCenter::RegisterService(const string& ServiceName,const string& ip,int port)
{
    lock_guard<mutex> lock(m_mutex);

    ServiceInfo info;
    info.ip = ip;
    info.port = port;
    info.load = 0;

    services[ServiceName].push_back(info);
    cout<<ServiceName<<"  "<<"registered  ip:"<<ip<<"  port:"<<port<<endl;
}

ServiceInfo RegistryCenter::FindService(const string& ServiceName)
{
    lock_guard<mutex> lock(m_mutex);
    if(services.find(ServiceName)!=services.end())
    {
        int min_load = services[ServiceName][0].load;
        int min = 0;
        for (int i = 1; i < services[ServiceName].size(); i++)
        {
            if (min_load > services[ServiceName][i].load)
            {
                min_load = services[ServiceName][i].load;
                min = i;
            }
        }
        return services[ServiceName][min];
    }
    else
        return {};
}

void RegistryCenter::UpdateLoad(const string& ServiceName,const string& ip,int load)
{
    lock_guard<mutex> lock(m_mutex);
    if(services.find(ServiceName)!=services.end())
    {
        for (int i = 0; i < services[ServiceName].size(); i++)
        {
            if (services[ServiceName][i].ip == ip)
            {
                services[ServiceName][i].load = load;
                break;
            }
        }
    }
}