#include "RpcClient.h"

vector<string> rpcCall(map<string, ServiceInfo> Services,string MethodName, initializer_list<string> Para) {
    //对服务列表的服务逐一尝试，如果返回结果就退出        
    for (auto &i : Services)
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

        //如果没有返回值就去下一个服务
        if (ret.returnValue.size() == 0)
            continue;

        return ret.returnValue;
    }
    
    //如果所有服务都无法返回，则返回空
    return vector<string>();
}

map<string, ServiceInfo> ServiceFind(const string ip, int port)
{
    //创建服务列表
    map<string, ServiceInfo> services;

    //与注册中心建立TCP连接
    int clientSocket = createTcpClient(ip.c_str(), port);
    if (clientSocket < 0) {
        close(clientSocket);
        return services;
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
    return services;
}

bool checkStartPara(int argc, char const *argv[],string &ip,int &port)
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
                port = std::stoi(argv[i+1]);
                if (port>65535||port<0)
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
            if (argc > i+1&&CheckIPAddrIsVaild(argv[i+1]))
            {
                ip = argv[i+1];
                hasip = true;
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

//RPC客户端
int main(int argc, char const *argv[])
{
    //判断启动参数
    int port;
    string ip;
    if(!checkStartPara(argc,argv,ip,port))
        return 0;

    //服务发现
    map<string, ServiceInfo> Services = ServiceFind(ip,port);
    if (Services.size()==0)
    {
        cout<<"当前无可用服务"<<endl;
        return 0;
    }
    

    //返回结果
    vector<string> ret_val = rpcCall(Services,"add",{"1","2","5","7","9"});
    for (auto &i : ret_val)
    {
        cout<<i<<endl;
    }
    
    return 0;
}

