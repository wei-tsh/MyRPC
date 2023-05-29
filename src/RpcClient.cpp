#include<iostream>
#include"TCP.h"

int main(int argc, char const *argv[])
{
    int a = createTcpServer(12345);
    int b = createTcpClient("127.0.0.1",12345);
    std::cout<<a<<" "<<b;
    return 0;
}
