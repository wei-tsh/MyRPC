#include "RpcClient.h"

vector<string> rpcCall(map<string, ServiceInfo> Services,string MethodName, initializer_list<string> Para) {
            
    for (auto &i : Services)
    {
        string ServiceName = i.first;
        RpcMessage Mes = createRpcMessage(ServiceName,MethodName,Para);

        // 建立TCP连接
        int clientSocket = createTcpClient(i.second.ip.c_str(),i.second.port);
        if (clientSocket < 0) {
            close(clientSocket);
            return vector<string>();
        }

        // 将消息编码为二进制数据
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
        RpcMessage ret = decode(responseData);
        return ret.returnValue;
    }
    
    return vector<string>();
}
map<string, ServiceInfo> ServiceFind(const string ip, int port)
{
    map<string, ServiceInfo> services;
    int clientSocket = createTcpClient(ip.c_str(), port);
    
    if (clientSocket < 0) {
        close(clientSocket);
        return services;
    }

    string Data = encodeRegMes(0,"",ServiceInfo());
    int Dlen = Data.length();
    
    int i  = send(clientSocket, Data.c_str(), Dlen, 0);
    
    string responseData;
    char buffer[1024] = { 0 };
    int len = 0;
    while ((len = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        responseData.append(buffer, len);
    }
    services = getServiceList(responseData);
    close(clientSocket);
    return services;
}

int main(int argc, char const *argv[])
{
    map<string, ServiceInfo> Services = ServiceFind("127.0.0.1",54468);

    vector<string> ret_val = rpcCall(Services,"add",{"1","2"});
    for (auto &i : ret_val)
    {
        cout<<i<<endl;
    }
    
    return 0;
}

