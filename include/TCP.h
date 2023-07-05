#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<regex>

//生成一个TCP服务端
int createTcpServer(const char* ip,int port,bool ipType);
//生成客户端连接，参数为服务端ip和端口
int createTcpClient(const char* ip,int port,bool ipType);
//利用正则表达式判断ip地址是否合法
bool CheckIPAddrIsIPv4(std::string str);
bool CheckIPAddrIsIPv6(std::string str);