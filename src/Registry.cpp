#include "Registry.h"

void RegistryCenter::RegisterService(const string& ServiceName,const string& ip,int port)
{
    lock_guard<mutex> lock(m_mutex);

    ServiceInfo info;
    info.ip = ip;
    info.port = port;
    info.load = 0;

    services[ServiceName] = info;
    cout<<ServiceName<<"  "<<"registered  ip:"<<ip<<"  port:"<<port<<endl;
}

string RegistryCenter::FindService()
{
    lock_guard<mutex> lock(m_mutex);
    return sendServiceList(services);
}

void RegistryCenter::UpdateLoad(const string& ServiceName,const string& ip,int load)
{
    lock_guard<mutex> lock(m_mutex);
    
}

int main(int argc, char const *argv[])
{
    RegistryCenter center;
    center.RegisterService("111","127.0.0.1",5555);
    int serversocket =createTcpServer(54468);
    
    if (serversocket < 0) {
        close(serversocket);
        cout<<"创建服务器失败"<<endl;
        return 0;
    }

    sockaddr_in addrClient;
    socklen_t len = sizeof(sockaddr);
    char buffer[1024];
    int datalen;
    while (true)
    {
        int sockcon = accept(serversocket,(struct sockaddr *)&addrClient,&len);
        
        string Data;
        memset(buffer,0,1024);
        datalen = 0;
        int a = recv(sockcon, buffer, sizeof(buffer), 0);
        Data.append(buffer);
        if (Data == "request")
        {
            string responseData = center.FindService();
            send(sockcon,responseData.c_str(),responseData.length(),0);
            close(sockcon);
            continue;
        }
        close(sockcon);      

    }
    close(serversocket);
    
    return 0;
}
