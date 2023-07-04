// #include"ThreadPool.h"
// #include<iostream>

// void test(int a = 55){
//     cout<<a<<endl;
// }

// int main(int argc, char const *argv[])
// {
//     ThreadPool pool(4,10);
    
//     for (int i = 0; i < 100; i++)
//     {
//         int a = i;
//         pool.addTask(test,a);
//     }

//     sleep(1);
// }

#include"RpcMes.h"
#include<iostream>

int main(int argc, char const *argv[])
{

    RpcMessage a = createRpcMessage("111","222",{"111","222","333"});
    string b = encode(a);
    cout<<b<<endl;

    return 0;
}


// #include<iostream>
// #include<RpcService.h>

// vector<string> add(vector<string> para)
// {
//     double sum;
//     try{
//         for (auto &i : para)
//     {
//         sum +=stod(i);
//     }
//     }catch(const invalid_argument& ia){
//         return vector<string>();
//     }
    
//     vector<string> retval;
//     retval.push_back(to_string(sum));
//     return retval;
// }

// int main(int argc, char const *argv[])
// {
//     RpcService one("one","127.0.0.1",45678);
//     one.registerMethod("add",add);
//     RpcMessage Mes = createRpcMessage("one","add",{"1","2","5.5"});
//     string b = encode(Mes);
//     cout<<b<<endl;
//     RpcMessage a = decode(b);
//     vector<string> ret = one.executeMethod(a);
//     for (auto &i : ret)
//     {
//         cout<<i<<endl;
//     }
    
//     return 0;
// }


// #include"TCP.h"
// #include<iostream>
// #include<string>

// int main(int argc, char const *argv[])
// {
//     int port;
//     bool hasport = false;
//     bool hasip = false;
//     std::string ip;
//     for (int i = 1; i < argc; i+=2)
//     {
//         if (strcmp(argv[i],"-p")==0)
//         {
//             if (argc > i+1)
//             {
//                 port = std::stoi(argv[i+1]);
//                 hasport = true;
//             }
//         }
//         else if(strcmp(argv[i],"-i")==0)
//         {
//             if (argc > i+1)
//             {
//                 ip = argv[i+1];
//                 hasip = true;
//             }
//         }
//         else if(strcmp(argv[i],"-h")==0)
//         {
//             std::cout<<"启动参数:\n-h 帮助参数\n-i 注册中心的ip地址（必须）\n-p 注册中心的端口（必须）"<<std::endl;
//             return 0;
//         }
//     }

//     if (!hasport||!hasip)
//     {
//         std::cout<<"-h 查看启动参数"<<std::endl;

//         return 0;
//     }
    
//     std::cout<<ip<<" "<<port<<std::endl;
    
//     return 0;
// }

// #include "TCP.h"
// #include<iostream>
// using namespace std;
// int main(int argc, char const *argv[])
// {
//     bool a =CheckIPAddrIsVaild("127.0.a.1");
//     cout<<a<<endl;
//     return 0;
// }
