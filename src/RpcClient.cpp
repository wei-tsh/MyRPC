#include<iostream>
#include"TCP.h"
#include"RpcMes.h"
#include "Registry.h"

int main(int argc, char const *argv[])
{
    RegistryCenter center;
    center.RegisterService("add","127.0.0.1",1000);
    center.RegisterService("sub","127.0.0.1",1005);
    center.RegisterService("add","127.0.0.2",1003);
    center.RegisterService("sub","127.0.0.2",1004);
    ServiceInfo a = center.FindService("add");
    cout<<a.ip<<"   "<<a.port<<endl;
    center.UpdateLoad("add",a.ip,1);
    ServiceInfo b = center.FindService("add");
    cout<<b.ip<<"   "<<b.port<<endl;
}
