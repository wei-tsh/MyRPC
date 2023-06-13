#include"RpcService.h"

RpcService::RpcService(string ServiceName)
{
    this->ServiceName = ServiceName;
}

void RpcService::registerMethod(string methodName, RpcMethod method)
{
    //将方法注册到服务中
    m_methods[methodName] = method;
    cout << "Method [" << methodName << "] registered" << endl;
}

vector<string> RpcService::executeMethod(const RpcMessage &Mes)
{
    //查找方法，如果没有方法，返回空
    if (m_methods.find(Mes.methodName) != m_methods.end()) {
        return m_methods[Mes.methodName](Mes.parameters);
    }
    return vector<string>();
}
