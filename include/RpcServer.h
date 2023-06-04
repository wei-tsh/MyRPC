#include"TCP.h"
#include"ThreadPool.h"
#include"RpcService.h"

//处理用户的连接
void handle(int sockcon);
//向服务器维护的map添加服务
void addService(string ServiceName,string ip,int host);