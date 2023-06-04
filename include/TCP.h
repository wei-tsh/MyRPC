#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

//生成一个TCP服务端
int createTcpServer(int port);
//生成客户端连接，参数为服务端ip和端口
int createTcpClient(const char* ip,int port);