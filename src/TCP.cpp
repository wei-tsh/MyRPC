#include "TCP.h"

int createTcpServer(const char* ip,int port,bool ipType) {
	//创建监听套接字
	int serverSocket;
	if (!ipType)
		serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	else
		serverSocket = socket(AF_INET6,SOCK_STREAM,IPPROTO_TCP);
	if (serverSocket < 0)
		return -1;
	
	//绑定地址
	if (!ipType)
	{
		sockaddr_in addrSer;
		memset(&addrSer,0,sizeof(sockaddr_in));
		addrSer.sin_family = AF_INET;
		addrSer.sin_addr.s_addr = inet_addr(ip);
		addrSer.sin_port= htons(port);
		if (bind(serverSocket,(sockaddr*)&addrSer, sizeof(sockaddr_in)) < 0)
		{
			close(serverSocket);
			return -1;
		}
	}
	else
	{
		sockaddr_in6 addrSer;
		memset(&addrSer,0,sizeof(sockaddr_in6));
		addrSer.sin6_family = AF_INET6;
		inet_pton(AF_INET6,ip,&addrSer.sin6_addr);
		addrSer.sin6_port= htons(port);
		if (bind(serverSocket,(sockaddr*)&addrSer, sizeof(sockaddr_in)) < 0)
		{
			close(serverSocket);
			return -1;
		}
	}

	//监听链接
	if (listen(serverSocket,SOMAXCONN) < 0)
	{
		close(serverSocket);
		return -1;
	}

	return serverSocket;
}

int createTcpClient(const char* ip, int port,bool ipType) {
	//创建客户端套接字
	int clientSocket;
	if (!ipType)
		clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	else
		clientSocket = socket(AF_INET6,SOCK_STREAM,IPPROTO_TCP);
	if (clientSocket < 0)
	{
		return -1;
	}

	//连接服务器
	if (!ipType)
	{
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
	}
	else
	{
		sockaddr_in6 addrCli;
		memset(&addrCli, 0, sizeof(sockaddr_in6));
		addrCli.sin6_family = AF_INET6;
		inet_pton(AF_INET6,ip,&addrCli.sin6_addr);
		addrCli.sin6_port = htons(port);
	}
	
	return clientSocket;
}

bool CheckIPAddrIsIPv4(std::string str)
{
    std::regex reg("((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
    return regex_match(str, reg);
}

bool CheckIPAddrIsIPv6(std::string str)
{
	std::regex reg("([\\da-fA-F]{1,4}:){6}((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^::([\\da-fA-F]{1,4}:){0,4}((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:):([\\da-fA-F]{1,4}:){0,3}((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){2}:([\\da-fA-F]{1,4}:){0,2}((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){3}:([\\da-fA-F]{1,4}:){0,1}((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){4}:((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){7}[\\da-fA-F]{1,4}$|^:((:[\\da-fA-F]{1,4}){1,6}|:)$|^[\\da-fA-F]{1,4}:((:[\\da-fA-F]{1,4}){1,5}|:)$|^([\\da-fA-F]{1,4}:){2}((:[\\da-fA-F]{1,4}){1,4}|:)$|^([\\da-fA-F]{1,4}:){3}((:[\\da-fA-F]{1,4}){1,3}|:)$|^([\\da-fA-F]{1,4}:){4}((:[\\da-fA-F]{1,4}){1,2}|:)$|^([\\da-fA-F]{1,4}:){5}:([\\da-fA-F]{1,4})?$|^([\\da-fA-F]{1,4}:){6}");
    return regex_match(str,reg);
}
