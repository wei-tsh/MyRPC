#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int createTcpServer(int port);
int createTcpClient(const char* ip,int port);