#include "Registry.h"

void RegistryCenter::RegisterService(const string& ServiceName,const string& ip,int port)
{
    //上锁
    lock_guard<mutex> lock(m_mutex);

    //初始化服务信息
    ServiceInfo info;
    info.ip = ip;
    info.port = port;
    info.load = 0;

    //将服务信息加入服务信息表
    services[ServiceName] = info;
    cout<<ServiceName<<"  "<<"registered  ip:"<<ip<<"  port:"<<port<<endl;
}

string RegistryCenter::FindService()
{
    //上锁
    lock_guard<mutex> lock(m_mutex);
    //返回服务列表
    return sendServiceList(services);
}

void RegistryCenter::UpdateLoad(const string& ServiceName,const string& ip,int load)
{
    lock_guard<mutex> lock(m_mutex);
    
}

int main(int argc, char const *argv[])
{
    //创建注册中心
    RegistryCenter center;
    
    //创建监听套接字
    int serversocket =createTcpServer(54468);
    if (serversocket < 0) {
        close(serversocket);
        cout<<"创建服务器失败"<<endl;
        return 0;
    }

    //监听用户连接
    sockaddr_in addrClient;
    socklen_t len = sizeof(sockaddr);
    char buffer[1024];
    while (true)
    {
        int sockcon = accept(serversocket,(struct sockaddr *)&addrClient,&len);

        //接收用户信息
        string Data;
        memset(buffer,0,1024);
        int a = recv(sockcon, buffer, sizeof(buffer), 0);
        Data.append(buffer);
        RegMes Mes = decodeRegMes(Data);

        //如果用户发送的信息种类为0,说明是用户请求服务发现
        if (Mes.type == 0)
        {
            //发送服务列表
            string responseData = center.FindService();
            send(sockcon,responseData.c_str(),responseData.length(),0);

            //关闭套接字
            close(sockcon);
            continue;
        }
        //如果用户种类为1，说明是服务端服务注册
        else if (Mes.type == 1)
        {
            //关闭套接字
            close(sockcon);

            //将服务添加到服务中心
            center.RegisterService(Mes.ServiceName,Mes.info.ip,Mes.info.port);
            continue;
        }

        //关闭与用户连接套接字
        close(sockcon);

    }
    //关闭监听
    close(serversocket);
    
    return 0;
}
