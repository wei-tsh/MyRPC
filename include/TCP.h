#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<regex>

//生成一个TCP服务端
int createTcpServer(int port);
//生成客户端连接，参数为服务端ip和端口
int createTcpClient(const char* ip,int port);
//利用正则表达式判断ip地址是否合法
bool CheckIPAddrIsVaild(std::string str);