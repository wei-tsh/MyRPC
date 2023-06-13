#include "Client.h"

bool checkStartPara(int argc, char const *argv[],string &ip,int &port)
{
    //判断有无输入ip和端口
    bool hasport = false;
    bool hasip = false;

    //读取数据
    for (int i = 1; i < argc; i+=2)
    {
        //判断是否有输入端口号
        if (strcmp(argv[i],"-p")==0)
        {
            if (argc > i+1)
            {
                port = std::stoi(argv[i+1]);
                if (port>65535||port<0)
                {
                    cout<<"端口号超出范围，-h 查看启动参数"<<endl;
                    return 0;
                }
                hasport = true;
            }
        }
        //判断是否有输入ip地址
        else if(strcmp(argv[i],"-i")==0)
        {
            if (argc > i+1&&CheckIPAddrIsVaild(argv[i+1]))
            {
                ip = argv[i+1];
                hasip = true;
            }
            else
            {
                cout<<"ip地址错误，-h 查看启动参数"<<endl;
                    return 0;
            }
            
        }
        //判断是否输入的是帮助参数
        else if(strcmp(argv[i],"-h")==0)
        {
            cout<<"启动参数:\n-h 帮助参数\n-i 注册中心的ip地址（必须）\n-p 注册中心的端口（必须）"<<endl;
            return 0;
        }
    }

    //如果缺少ip或者端口号，提示用户查看参数
    if (!hasport||!hasip)
    {
        cout<<"输入错误，-h 查看启动参数"<<endl;
        return 0;
    }

    return 1;
}

//RPC客户端
int main(int argc, char const *argv[])
{
    //判断启动参数
    int port;
    string ip;
    if(!checkStartPara(argc,argv,ip,port))
        return 0;

    RpcClient client(ip,port);

    //返回结果
    vector<string> ret_val = client.rpcCall("add",{"1","2","5","7","9"});
    for (auto &i : ret_val)
    {
        cout<<i<<endl;
    }
    
    return 0;
}

