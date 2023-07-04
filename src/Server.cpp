#include "Rpc.h"

//测试函数
string add(vector<string>& para,vector<string>& retval)
{
    double sum;
    try{
        for (auto &i : para)
    {
        sum +=stod(i);
    }
    }catch(const invalid_argument& ia){
        return "para error";
    }
    retval.push_back(to_string(sum));
    return string();
}

string minuses(vector<string>& para,vector<string>& retval)
{
    double sum;
    try{
        for (auto &i : para)
        {
            if (strcmp(i.c_str(),para[0].c_str()))
            {
                sum+=stod(i);
                continue;
            }
            sum -=stod(i);
        }
    }catch(const invalid_argument& ia){
        return "para error";
    }
    retval.push_back(to_string(sum));
    return string();
}

string swaps(vector<string>& para,vector<string>& retval){
    return string();
}

string multiply(vector<string>& para,vector<string>& retval){
    return string();
}

string divide(vector<string>& para,vector<string>& retval){
    return string();
}

string power(vector<string>& para,vector<string>& retval){
    return string();
}

string root(vector<string>& para,vector<string>& retval){
    return string();
}

string Time(vector<string>& para,vector<string>& retval){

}
//勾股定理
string Pyth(vector<string>& para,vector<string>& retval){

}

string Mrandom(vector<string>& para,vector<string>& retval){

}

//RPC服务器
int main(int argc, char const *argv[])
{
    RpcServer server(argc,argv,"one");

    //注册方法
    server.addMethod("add",add);
    server.addMethod("minuses",minuses);
    server.addMethod("power",power);
    server.addMethod("swaps",swaps);
    server.addMethod("multiply",multiply);
    server.addMethod("divide",divide);
    server.addMethod("root",root);
    server.addMethod("Time",Time);
    server.addMethod("Pyth",Pyth);
    server.addMethod("Mrandom",Mrandom);
    server.addMethod("add",add);

    server.start();

    return 0;
}