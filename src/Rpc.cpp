#include "Rpc.h"

//服务器本地服务列表
map<string,RpcService> ServicesList;

RpcServer::RpcServer(string ip, int port, string regip, int regport)
{
    this->IP = ip;
    this->port = port;
    this->Regip = regip;
    this->RegPort = regport;
    pool = new ThreadPool(10,15);
}

void handle(int sockcon,int load)
{
    char buffer[1024];
    memset(buffer,0,1024);
    
    //接收RPC信息
    string Data;
    recv(sockcon, buffer, sizeof(buffer), 0);
    Data.append(buffer);
    RpcMessage mes = decode(Data);
    
    //在本地服务列表查找服务，如果没有就不处理RPC信息
    if (ServicesList.find(mes.serviceName) != ServicesList.end()) 
    {
        if (!strcmp(mes.methodName.c_str(),"heartCheck"))
        {
            mes.returnValue.push_back(to_string(load));
        }
        else
        {
            string error = ServicesList[mes.serviceName].executeMethod(mes);
            mes.error = error;
        }
    }

    //回复RPC信息
    string retData = encode(mes);
    send(sockcon,retData.c_str(),retData.length(),0);
    close(sockcon);
}

void RpcServer::addService(string ServiceName)
{
    ServicesList[ServiceName] = RpcService(ServiceName);
}

void RpcServer::addMethod(string ServiceName,string MethodName, RpcMethod method)
{
    //在服务列表查找服务，如果没有就不处理RPC信息
    if (ServicesList.find(ServiceName) != ServicesList.end()) 
    {
        ServicesList[ServiceName].registerMethod(MethodName,method);
    }
    else
    {
        cout<<"找不到服务名："<<ServiceName<<"，方法："<<MethodName<<"注册失败"<<endl;
    }
    
}

void RpcServer::start()
{
    registerService();
    //创建监听套接字
    int serversocket =createTcpServer(port);
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

void RpcServer::registerService()
{
    //创建与注册中心的连接
    int clientsocket = createTcpClient(Regip.c_str(),RegPort);
    if(clientsocket < 0)
    {
        cout<<"连接不上服务器，服务注册失败"<<endl;
        return;
    }

    
    for (auto &i : ServicesList)
    {
        // 向服务器发送注册请求
        ServiceInfo serinfo;
        serinfo.ip = IP;
        serinfo.port = port;
        serinfo.load = 0;
        string Data = encodeRegMes(1,i.second.getServiceName(),serinfo);

        // 发送消息
        send(clientsocket, Data.c_str(), Data.length(), 0);
    }

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
        int clientSocket = createTcpClient(i.second.ip.c_str(),i.second.port);
        if (clientSocket < 0) {
            close(clientSocket);
            continue;
        }

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

void RpcClient::ServiceFind()
{
    //与注册中心建立TCP连接
    int clientSocket = createTcpClient(Regip.c_str(), RegPort);
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

RpcClient::RpcClient(string regip,int regport)
{
    this->Regip = regip;
    this->RegPort = regport;
    ServiceFind();
    if (services.size()==0)
    {
        cout<<"当前无可用服务"<<endl;
    }
}