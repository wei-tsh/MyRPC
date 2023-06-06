#include "RpcServer.h"

//服务器本地服务列表
map<string,RpcService> ServicesList;

//测试函数
vector<string> add(vector<string> para)
{
    
    double sum;
    try{
        for (auto &i : para)
    {
        sum +=stod(i);
    }
    }catch(const invalid_argument& ia){
        return vector<string>();
    }
    vector<string> retval;
    retval.push_back(to_string(sum));
    return retval;
}

//处理连接套接字
void handle(int sockcon)
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
        vector<string> retval = ServicesList[mes.serviceName].executeMethod(mes);
        for (auto &i : retval)
        {
            mes.returnValue.push_back(i);
        }
    }

    //回复RPC信息
    string retData = encode(mes);
    send(sockcon,retData.c_str(),retData.length(),0);
    close(sockcon);
}

//向本地服务列表添加服务并向注册中心注册服务
void addService(string ServiceName,string ip,int host,string regip,int regport)
{
    ServicesList[ServiceName] = RpcService(ServiceName,ip,host);
    registerService(ServicesList[ServiceName],regip,regport);
}

bool checkStartPara(int argc, char const *argv[],string &ip,int &port,string &regip,int &regport)
{
    //判断有无输入ip和端口
    bool hasport = false;
    bool hasregip = false;
    bool hasregport = false;

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
        else if(strcmp(argv[i],"-r")==0)
        {
            if (argc > i+1 && CheckIPAddrIsVaild(argv[i+1]))
            {
                regip = argv[i+1];
                hasregip = true;
            }else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        else if (strcmp(argv[i],"-a")==0)
        {
            if (argc > i+1)
            {
                regport = std::stoi(argv[i+1]);
                hasregport = true;
            }
            else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        //判断是否输入的是帮助参数
        else if(strcmp(argv[i],"-h")==0)
        {
            cout<<"启动参数:\n-h 帮助参数\n-i 服务器的ip地址(默认为0.0.0.0)\n-p 服务器监听的端口（必须）"<<endl;
            cout<<"-r 注册中心的ip地址（必须）\n-a 注册中心监听的端口（必须）"<<endl;
            return 0;
        }
    }
    //如果端口号，提示用户查看参数
    if (!hasport||!hasregip||!hasregport)
    {
        cout<<"输入错误，-h 查看启动参数"<<endl;

        return 0;
    }

    return 1;
}

//RPC服务器
int main(int argc, char const *argv[])
{
    string ip = "0.0.0.0";
    string regip;
    int port;
    int regport;
    if(!checkStartPara(argc,argv,ip,port,regip,regport))
    {
        return 0;
    }
    cout<<ip<<" "<<port<<"  "<<regip<<" "<<regport<<endl;
    //添加服务
    addService("one",ip,port,regip,regport);

    //注册方法
    ServicesList["one"].registerMethod("add",add);

    //创建线程池
    ThreadPool pool(5,15);

    //创建监听套接字
    int serversocket =createTcpServer(45678);
    if (serversocket < 0) {
        close(serversocket);
        cout<<"创建服务器失败"<<endl;
        return 0;
    }

    //监听客户的连接
    sockaddr_in addrClient;
    socklen_t len = sizeof(sockaddr);
    while (true)
    {
        int sockcon = accept(serversocket,(struct sockaddr *)&addrClient,&len);
        
        //向线程池添加任务
        pool.addTask(handle,sockcon);
    }

    //关闭套接字
    close(serversocket);
    
    return 0;
}