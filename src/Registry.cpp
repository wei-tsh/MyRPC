#include "Registry.h"

RegistryCenter::RegistryCenter()
{
    HeartCheck = thread(heartCheck,this);
}

void RegistryCenter::RegisterService(const string &ServiceName, const string &ip, int port)
{
    //上锁
    lock_guard<mutex> lock(m_mutex);

    //初始化服务信息
    services[ServiceName].ip = ip;
    services[ServiceName].port = port;
    services[ServiceName].load = 0;

    //将服务信息加入服务信息表
    cout<<ServiceName<<"  "<<"registered  ip:"<<ip<<"  port:"<<port<<endl;
}

string RegistryCenter::FindService()
{
    //上锁
    lock_guard<mutex> lock(m_mutex);
    //返回服务列表
    return sendServiceList(services);
}

void RegistryCenter::heartCheck(RegistryCenter *Center)
{
    while (true)
    {
        sleep(10);
        vector<string> deletemap;
        for (auto &i : Center->services)
        {
            RpcMessage mes = createRpcMessage(i.first,"heartCheck",{});
            string data = encode(mes);
            int clientSocket = createTcpClient(i.second.ip.c_str(),i.second.port,0);
            if (clientSocket < 0) {
                close(clientSocket);
                deletemap.push_back(i.first);
                continue;
            }

            struct timeval tv;
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

            // 发送消息
            send(clientSocket, data.c_str(), data.length(), 0);

            // 接收消息
            string responseData;
            char buffer[1024] = { 0 };
            int len = 0;
            while ((len = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
                responseData.append(buffer, len);
            }
            // 关闭TCP连接
            close(clientSocket);
            //将返回信息转化成RPC报文
            RpcMessage ret = decode(responseData);
            if (ret.returnValue.size() == 0)
            {
                deletemap.push_back(i.first);
            }
            else
            {
                int load = stoi(ret.returnValue[0]);
                Center->UpdateLoad(i.first,load);
            }
        }
        for (auto &i : deletemap)
        {
            Center->DeleteService(i);
        }
    }
}

void RegistryCenter::DeleteService(string ServiceName)
{
    lock_guard<mutex> lock(m_mutex);
    cout<<ServiceName<<"  "<<"deleted"<<endl;
    services.erase(ServiceName);
}

void RegistryCenter::UpdateLoad(const string &ServiceName, int load)
{
    lock_guard<mutex> lock(m_mutex);
    services[ServiceName].load = load;

    cout<<ServiceName<<"  "<<"updated  load:"<<load<<endl;
}

int main(int argc, char const *argv[])
{
    //创建注册中心
    RegistryCenter center;
    
    //创建监听套接字
    int serversocket =createTcpServer("0.0.0.0",12345,0);
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
        recv(sockcon, buffer, sizeof(buffer), 0);
        Data.append(buffer);
        RegMes Mes = decodeRegMes(Data);

        //如果用户发送的信息种类为0,说明是用户请求服务发现
        if (Mes.type == 0)
        {
            //发送服务列表
            string responseData = center.FindService();
            send(sockcon,responseData.c_str(),responseData.length(),0);
        }
        //如果用户种类为1，说明是服务端服务注册
        else if (Mes.type == 1)
        {
            //将服务添加到服务中心
            center.RegisterService(Mes.ServiceName,Mes.info.ip,Mes.info.port);
        }

        //关闭与用户连接套接字
        close(sockcon);

    }
    //关闭监听
    close(serversocket);
    
    return 0;
}
