#include "Rpc.h"

RpcService* service;

RpcServer::RpcServer(int argc, char const *argv[],string serviceName)
{
    startParaOK =checkStartPara(argc,argv);
    setServiceName(serviceName);
    service = new RpcService();
    pool = new ThreadPool(10,15);
}

RpcServer::~RpcServer()
{
    pool->~ThreadPool();
    delete service;
}

void handle(int sockcon,int load)
{
    char buffer[1024];
    memset(buffer,0,1024);

    //设置超时
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sockcon, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    
    //接收RPC信息
    string Data;
    recv(sockcon, buffer, sizeof(buffer), 0);
    Data.append(buffer);
    RpcMessage mes = decode(Data);
    
    //在本地服务列表查找服务，如果没有就不处理RPC信息
    if (!strcmp(mes.methodName.c_str(),"heartCheck"))
    {
        mes.returnValue.push_back(to_string(load));
    }
    else
    {
        string error = service->executeMethod(mes);
        mes.error = error;
    }

    //回复RPC信息
    string retData = encode(mes);
    send(sockcon,retData.c_str(),retData.length(),0);
    close(sockcon);
}

void RpcServer::addMethod(string MethodName, RpcMethod method)
{
    service->registerMethod(MethodName,method);
}

void RpcServer::start()
{
    if (!startParaOK)
    {
        return;
    }
    
    registerService();
    //创建监听套接字
    int serversocket =createTcpServer(IP.c_str(),port,IPtype);
    if (serversocket < 0) {
        close(serversocket);
        cout<<"创建服务器失败"<<endl;
        return ;
    }

    //监听客户的连接
    sockaddr_in addrClient;
    socklen_t len = sizeof(sockaddr);
    while (true)
    {
        int sockcon = accept(serversocket,(struct sockaddr *)&addrClient,&len);
        //向线程池添加任务
        pool->addTask(handle,sockcon,pool->getBusyNum());
    }

    //关闭套接字
    close(serversocket);
}

bool RpcServer::checkStartPara(int argc, char const *argv[])
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
            if (argc > i+1)
            {
                int a = CheckIPAddrIsIPv4(argv[i+1]);
                int b = CheckIPAddrIsIPv6(argv[i+1]);
                if (a||b)
                {
                    IP = argv[i+1];
                    if(a){
                        IPtype = 0;
                    }
                    else{
                        IPtype = 1;
                    }
                }
            }else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        //判断是否输入的是帮助参数
        else if(strcmp(argv[i],"-h")==0)
        {
            cout<<"启动参数:\n-h 帮助参数\n-i 服务器的ip地址(默认为0.0.0.0)\n-p 服务器监听的端口（必须）"<<endl;
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

void RpcServer::registerService()
{
    //创建与注册中心的连接
    int clientsocket = createTcpClient(registryIP.c_str(),registryPort,IPtype);
    if(clientsocket < 0)
    {
        cout<<"连接注册中心失败"<<endl;
        return;
    }

    // 向服务器发送注册请求
    ServiceInfo serinfo;
    serinfo.ip = IP;
    serinfo.port = port;
    serinfo.load = 0;
    string Data = encodeRegMes(1,ServiceName,serinfo);

    // 发送消息
    send(clientsocket, Data.c_str(), Data.length(), 0);

    // 关闭TCP连接
    close(clientsocket);
}

vector<string> RpcClient::rpcCall(string MethodName, initializer_list<string> Para)
{
    for (auto &i : services)
    {
        //创建RPC协议报文
        string ServiceName = i.first;
        RpcMessage Mes = createRpcMessage(ServiceName,MethodName,Para);

        // 建立TCP连接
        int clientSocket = createTcpClient(i.second.ip.c_str(),i.second.port,IPtype);
        if (clientSocket < 0) {
            close(clientSocket);
            continue;
        }

        //设置超时
        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        // 将消息编码为json格式
        string Data = encode(Mes);
        // 发送消息
        send(clientSocket, Data.c_str(), Data.length(), 0);

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

        if (ret.error.size() > 0)
        {
            cout<<"error:"<<ret.error<<endl;
            return vector<string>();
        }
        
        //如果没有返回值就去下一个服务
        if (ret.returnValue.size() == 0)
            continue;

        return ret.returnValue;
    }
    
    //如果所有服务都无法返回，则返回空
    return vector<string>();
}

bool RpcClient::checkStartPara(int argc, char const *argv[])
{
    //判断有无输入ip和端口
    bool hasport = false;
    bool hasip = false;
    //读取数据
    for (int i = 1; i < argc; i+=2)
    {
        //判断是否有输入端口号
        if (strcmp(argv[i],"-p")==0)
        {
            if (argc > i+1)
            {
                TargetPort = std::stoi(argv[i+1]);
                if (TargetPort>65535||TargetPort<0)
                {
                    cout<<"端口号超出范围，-h 查看启动参数"<<endl;
                    return 0;
                }
                hasport = true;
            }
        }
        //判断是否有输入ip地址
        else if(strcmp(argv[i],"-i")==0)
        {
            if (argc > i+1)
            {
                int a = CheckIPAddrIsIPv4(argv[i+1]);
                int b = CheckIPAddrIsIPv6(argv[i+1]);
                if (a||b)
                {
                    Targetip = argv[i+1];
                    hasip = true;
                    if(a){
                        IPtype = 0;
                    }
                    else{
                        IPtype = 1;
                    }
                }
            }
            else
            {
                cout<<"ip地址错误，-h 查看启动参数"<<endl;
                    return 0;
            }
        }
        //判断是否输入的是帮助参数
        else if(strcmp(argv[i],"-h")==0)
        {
            cout<<"启动参数:\n-h 帮助参数\n-i 注册中心的ip地址（必须）\n-p 注册中心的端口（必须）"<<endl;
            return 0;
        }
    }
    //如果缺少ip或者端口号，提示用户查看参数
    if (!hasport||!hasip)
    {
        cout<<"输入错误，-h 查看启动参数"<<endl;
        return 0;
    }

    return 1;
}

void RpcClient::ServiceFind()
{
    //与注册中心建立TCP连接
    int clientSocket = createTcpClient(Targetip.c_str(), TargetPort,IPtype);
    if (clientSocket < 0) {
        close(clientSocket);
        return ;
    }

    //向注册中心发送请求报文
    string Data = encodeRegMes(0,"",ServiceInfo());
    int Dlen = Data.length();
    send(clientSocket, Data.c_str(), Dlen, 0);
    
    //接受返回的服务列表
    string responseData;
    char buffer[1024] = { 0 };
    int len = 0;
    while ((len = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        responseData.append(buffer, len);
    }

    //将返回的服务列表存入表中
    services = getServiceList(responseData);

    //关闭套接字
    close(clientSocket);
}

RpcClient::RpcClient(int argc, char const *argv[])
{
    if (argc > 1 && checkStartPara(argc,argv))
    {
        ServiceInfo serverinfo;
        serverinfo.ip = Targetip;
        serverinfo.port = TargetPort;
        serverinfo.load = 0;
        services["direct"] = serverinfo;
    }
    else if (argc == 1)
    {
        Targetip = registryIP;
        TargetPort = registryPort;
        ServiceFind();
        if (services.size()==0)
        {
            cout<<"当前无可用服务"<<endl;
        }
    }
}