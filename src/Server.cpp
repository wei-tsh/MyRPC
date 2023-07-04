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

bool checkStartPara(int argc, char const *argv[],string &ip,int &port,string &regip,int &regport)
{
    //判断有无输入ip和端口
    bool hasport = false;
    bool hasregip = false;
    bool hasregport = false;

    //读取数据
    for (int i = 1; i < argc; i+=2)
    {
        //判断是否有输入端口号
        if (strcmp(argv[i],"-p")==0)
        {
            if (argc > i+1)
            {
                port = std::stoi(argv[i+1]);
                hasport = true;
            }
            else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        //判断是否有输入ip地址
        else if(strcmp(argv[i],"-i")==0)
        {
            if (argc > i+1 && CheckIPAddrIsVaild(argv[i+1]))
            {
                ip = argv[i+1];
            }else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
            
        }
        else if(strcmp(argv[i],"-r")==0)
        {
            if (argc > i+1 && CheckIPAddrIsVaild(argv[i+1]))
            {
                regip = argv[i+1];
                hasregip = true;
            }else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        else if (strcmp(argv[i],"-a")==0)
        {
            if (argc > i+1)
            {
                regport = std::stoi(argv[i+1]);
                hasregport = true;
            }
            else
            {
                cout<<"输入错误，-h 查看启动参数"<<endl;
                return 0;
            }
        }
        //判断是否输入的是帮助参数
        else if(strcmp(argv[i],"-h")==0)
        {
            cout<<"启动参数:\n-h 帮助参数\n-i 服务器的ip地址(默认为0.0.0.0)\n-p 服务器监听的端口（必须）"<<endl;
            cout<<"-r 注册中心的ip地址（必须）\n-a 注册中心监听的端口（必须）"<<endl;
            return 0;
        }
    }
    //如果端口号，提示用户查看参数
    if (!hasport||!hasregip||!hasregport)
    {
        cout<<"输入错误，-h 查看启动参数"<<endl;

        return 0;
    }

    return 1;
}

//RPC服务器
int main(int argc, char const *argv[])
{
    string ip = "0.0.0.0";
    string regip;
    int port;
    int regport;
    if(!checkStartPara(argc,argv,ip,port,regip,regport))
    {
        return 0;
    }
    cout<<ip<<" "<<port<<"  "<<regip<<" "<<regport<<endl;

    RpcServer server(ip,port,regip,regport);

    //添加服务
    server.addService("one");
    server.addService("two");

    //注册方法
    server.addMethod("one","add",add);
    server.addMethod("one","minuses",minuses);
    server.addMethod("one","power",power);
    server.addMethod("one","swaps",swaps);
    server.addMethod("one","multiply",multiply);
    server.addMethod("one","divide",divide);
    server.addMethod("one","root",root);
    server.addMethod("one","Time",Time);
    server.addMethod("one","Pyth",Pyth);
    server.addMethod("one","Mrandom",Mrandom);
    server.addMethod("two","add",add);

    server.start();

    return 0;
}