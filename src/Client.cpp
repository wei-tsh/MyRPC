#include "Rpc.h"

//RPC客户端的对象
int main(int argc, char const *argv[])
{
    RpcClient client(argc,argv);

    //返回结果
    vector<string> ret_val = client.rpcCall("add",{"1","5","7","9"});
    for (auto &i : ret_val)
    {
        cout<<i<<endl;
    }
    
    return 0;
}

