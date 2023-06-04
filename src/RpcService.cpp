#include"RpcService.h"

RpcService::RpcService(string ServiceName, string ip, int port)
{
    this->ServiceName = ServiceName;
    this->ip = ip;
    this->port = port;
}

void RpcService::registerMethod(string methodName, RpcMethod method)
{
    m_methods[methodName] = method;
    cout << "Method [" << methodName << "] registered" << endl;
}

vector<string> RpcService::executeMethod(const RpcMessage &Mes)
{
    if (m_methods.find(Mes.methodName) != m_methods.end()) {
        return m_methods[Mes.methodName](Mes.parameters);
    }
    return vector<string>();
}
void registerService(RpcService service,string ip,int host)
{
    int clientsocket = createTcpClient(ip.c_str(),host);
    if(clientsocket < 0)
    {
        cout<<"连接不上服务器，服务注册失败"<<endl;
        return;
    }

    // 将消息编码为二进制数据
    ServiceInfo serinfo;
    serinfo.ip = service.getIp();
    serinfo.port = service.getPort();
    serinfo.load = 0;
    string Data = encodeRegMes(1,service.getServiceName(),serinfo);

    // 发送消息
    send(clientsocket, Data.c_str(), Data.length(), 0);

    // 关闭TCP连接
    close(clientsocket);
}