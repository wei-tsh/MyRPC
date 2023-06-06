#include "TCP.h"

int createTcpServer(int port) {
	//创建监听套接字
	int serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (serverSocket < 0)
	{
		return -1;
	}
	//绑定地址
	sockaddr_in addrSer;
	memset(&addrSer,0,sizeof(sockaddr_in));
	addrSer.sin_family = AF_INET;
	addrSer.sin_addr.s_addr = htonl(INADDR_ANY);
	addrSer.sin_port= htons(port);
	if (bind(serverSocket,(sockaddr*)&addrSer, sizeof(sockaddr_in)) < 0)
	{
		close(serverSocket);
		return -1;
	}

	//监听链接
	if (listen(serverSocket,SOMAXCONN) < 0)
	{
		close(serverSocket);
		return -1;
	}

	return serverSocket;
}

int createTcpClient(const char* ip, int port) {
	//创建客户端套接字
	int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket < 0)
	{
		return -1;
	}

	//连接服务器
	sockaddr_in addrCli;
	memset(&addrCli, 0, sizeof(sockaddr_in));
	addrCli.sin_family = AF_INET;
	addrCli.sin_addr.s_addr = inet_addr(ip);
	addrCli.sin_port = htons(port);
	if (connect(clientSocket,(sockaddr*)&addrCli,sizeof(sockaddr_in)) < 0)
	{
		close(clientSocket);
		return -1;
	}
	
	return clientSocket;
}

bool CheckIPAddrIsVaild(std::string str)
{
    std::regex reg("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");

    return regex_match(str, reg);
}
