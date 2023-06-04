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
    RpcMessage c = decode("{\"ServiceName\":\"one\",\"MethodName\":\"add\",\"Parameters\":[\"1\",\"2\"],\"ReturnValues\":[\"3.000000\"]}");
    for (auto &i : c.returnValue)
    {
        cout<<i<<endl;
    }
    

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
