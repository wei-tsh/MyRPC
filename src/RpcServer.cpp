#include "RpcServer.h"

map<string,RpcService> ServicesList;

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

void handle(int sockcon)
{
    char buffer[1024];
    memset(buffer,0,1024);
    
    //接收信息
    string Data;
    recv(sockcon, buffer, sizeof(buffer), 0);
    Data.append(buffer);
    RpcMessage mes = decode(Data);
    
    //处理信息
    if (ServicesList.find(mes.serviceName) != ServicesList.end()) {
        vector<string> retval = ServicesList[mes.serviceName].executeMethod(mes);
        for (auto &i : retval)
        {
            mes.returnValue.push_back(i);
        }
    }

    //回复信息
    string retData = encode(mes);
    send(sockcon,retData.c_str(),retData.length(),0);
    close(sockcon);
}

void addService(string ServiceName,string ip,int host)
{
    ServicesList[ServiceName] = RpcService(ServiceName,ip,host);
    registerService(ServicesList[ServiceName],"127.0.0.1",54468);
}

int main(int argc, char const *argv[])
{
    addService("one","127.0.0.1",45678);
    ServicesList["one"].registerMethod("add",add);
    ThreadPool pool(5,15);
    int serversocket =createTcpServer(45678);
    
    if (serversocket < 0) {
        close(serversocket);
        cout<<"创建服务器失败"<<endl;
        return 0;
    }

    sockaddr_in addrClient;
    socklen_t len = sizeof(sockaddr);
    while (true)
    {
        int sockcon = accept(serversocket,(struct sockaddr *)&addrClient,&len);
        pool.addTask(handle,sockcon);
    }
    close(serversocket);
    
    return 0;
}