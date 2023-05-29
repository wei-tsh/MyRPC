#include<iostream>
#include"TCP.h"
#include"RpcMes.h"

int main(int argc, char const *argv[])
{
    RpcMessage a;
    a.methodName = "222";
    a.serviceName = "ddd";
    a.parameterCount = 3;
    a.parameters.push_back("a");
    a.parameters.push_back("b");
    a.parameters.push_back("c");
    a.returnValue = "111";
    std::string b = encode(a);
    RpcMessage c = decode(b);
    std::cout<<b<<std::endl;
    std::cout<<c.parameters[0]<<" "<<c.parameters[1]<<" "<<c.parameters[2]<<" ";
    return 0;
}
