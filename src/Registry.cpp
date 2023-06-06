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

bool checkStartPara(int argc, char const *argv[],string &ip,int &port)
{
    //判断有无输入ip和端口
    bool hasport = false;

    //读取数据
    for (int i = 1; i < argc; i+=2)
    {
        //判断是否有输入端口号
        if (strcmp(argv[i],"-p")==0)
        {
            if (argc > i+1)
            {
                port = std::stoi(argv[i+1]);
                hasport = true;
            }
            else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        //判断是否有输入ip地址
        else if(strcmp(argv[i],"-i")==0)
        {
            if (argc > i+1 && CheckIPAddrIsVaild(argv[i+1]))
            {
                ip = argv[i+1];
            }else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
            
        }
        //判断是否输入的是帮助参数
        else if(strcmp(argv[i],"-h")==0)
        {
            cout<<"启动参数:\n-h 帮助参数\n-i 注册中心的ip地址(默认为0.0.0.0)\n-p 注册中心的端口（必须）"<<endl;
            return 0;
        }
    }
    //如果端口号，提示用户查看参数
    if (!hasport)
    {
        cout<<"输入错误，-h 查看启动参数"<<endl;

        return 0;
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    string ip = "0.0.0.0";
    int port;
    if(!checkStartPara(argc,argv,ip,port))
    {
        return 0;
    }

    //创建注册中心
    RegistryCenter center;
    
    //创建监听套接字
    int serversocket =createTcpServer(port);
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
            center.RegisterService(Mes.ServiceName,inet_ntoa(addrClient.sin_addr),Mes.info.port);
            continue;
        }

        //关闭与用户连接套接字
        close(sockcon);

    }
    //关闭监听
    close(serversocket);
    
    return 0;
}
