#include"TCP.h"
#include<iostream>
int main(int argc, char const *argv[])
{
    int serversocket = createTcpServer(12556);
    std::cout<<serversocket<<std::endl;
    if (serversocket < 0) {
        close(serversocket);
        std::cout<<"创建服务器失败"<<std::endl;
        return 0;
    }
    sockaddr_in addrClient;
    socklen_t len = sizeof(sockaddr);
    std::cout<<"111"<<std::endl;
    int datalen;
    while (true)
    {
        int sockcon = accept(serversocket,(struct sockaddr *)&addrClient,&len);
        std::cout<<sockcon<<std::endl;
        std::string Data;
        datalen = 0;
    
        const int bufLen = 25600;
	    char buffer[bufLen];
        std::cout<<"222"<<std::endl;
        int a = 0;
        a = recv(sockcon, buffer, bufLen, 0);
        Data.append(buffer,a);
        std::cout<<a<<std::endl;
        std::cout<<Data<<std::endl;
        close(sockcon);
    }
    
    close(serversocket);

    return 0;
}
