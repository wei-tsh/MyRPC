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
void addService(string ServiceName,string ip,int host)
{
    ServicesList[ServiceName] = RpcService(ServiceName,ip,host);
    registerService(ServicesList[ServiceName],"127.0.0.1",54468);
}

//RPC服务器
int main(int argc, char const *argv[])
{
    //添加服务
    addService("one","127.0.0.1",45678);

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