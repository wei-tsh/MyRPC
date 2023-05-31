#include "RpcClient.h"

string rpcCall(const string ip, int port, string ServiceName,int ParaCount, initializer_list<string> Para) {
            //注册中心
            ServiceMes request;
            request.type = 1;
            request.ServiceName = ServiceName;
            string reqData = SerEncode(request);
            // 与注册中心建立TCP连接
            int requestSocket = createTcpClient(ip.c_str(), port);
            if (requestSocket < 0) {
                close(requestSocket);
                return "";
            }
            send(requestSocket, reqData.c_str(), reqData.length(), 0);
            string ServiceDate;
            char buffer[1024] = { 0 };
            int len = 0;
            while ((len = recv(requestSocket, buffer, sizeof(buffer), 0)) > 0) {
                ServiceDate.append(buffer, len);
                }
            // 关闭TCP连接
            close(requestSocket);
            request = SerDecode(ServiceDate);
            RpcMessage Mes = createRpcMessage(ServiceName,ParaCount,Para);
            // 建立TCP连接
            int clientSocket = createTcpClient(request.ip.c_str(), request.port);
            if (clientSocket < 0) {
                close(clientSocket);
                return "";
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
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

