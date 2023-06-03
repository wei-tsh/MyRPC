#include "RpcServer.h"

RpcService::RpcService(string ServiceName, string ip, int port)
{
    this->ServiceName = ServiceName;
    this->ip = ip;
    this->port = port;
}

void RpcService::registerService()
{
    int clientsocket = createTcpClient(registry_ip.c_str(),registry_host);
    if(clientsocket < 0)
    {
        cout<<"连接不上服务器，服务注册失败"<<endl;
        return;
    }

    // 将消息编码为二进制数据
    ServiceInfo serinfo;
    serinfo.ip = this->ip;
    serinfo.port = this->port;
    serinfo.load = 0;
    string Data = encodeRegMes(1,this->ServiceName,serinfo);

    // 发送消息
    send(clientsocket, Data.c_str(), Data.length(), 0);

    // 关闭TCP连接
    close(clientsocket);
}

void RpcService::setRegistryAddress(string ip, int host)
{
    this->registry_ip = ip;
    this->registry_host = host;
}

void RpcService::registerMethod(string &methodName, RpcMethod method)
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

int main(int argc, char const *argv[])
{
    RpcService one("one","127.0.0.1",45678);
    one.setRegistryAddress("127.0.0.1",54468);
    one.registerService();

    return 0;
}