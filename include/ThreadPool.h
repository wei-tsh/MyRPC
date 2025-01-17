#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
#include <iostream>
#include <unistd.h>

using namespace std;

//线程池执行的任务
struct Task
{
    function<void(int,int)> f;          //线程执行的函数
    int arg;                            //函数的参数
    int load;                           //线程池的负载

    //构造函数
    Task(function<void(int,int)> F,int Arg,int Load){f = F; arg = Arg;load=Load;}
    Task(){};
};

//线程池，拥有1个管理线程以及多个执行任务的线程
class ThreadPool
{
public:
    //构造函数
    ThreadPool(int min,int max);
    //析构函数
    ~ThreadPool();

    //向任务队列添加任务
    void addTask(function<void(int,int)> f,int arg,int load);

    //得到正在执行任务的线程的数量
    int getBusyNum();
    
    //得到线程池中存在的线程的数量
    int getAliveNum();

private:
    //执行任务的线程
    static void worker(ThreadPool* pool);

    //管理线程池的线程
    static void manager(ThreadPool* pool);

    //关闭多余线程的函数
    void threadExit();

private:
    queue<Task> tasks;                          //任务队列

    thread managerID;                           //管理者线程ID
    vector<thread> workerIDs;                   //执行任务的线程ID，用容器管理

    int minNum;                                 //线程池中最少容纳的线程数
    int maxNum;                                 //线程池中最大容纳的线程数
    atomic<int> busyNum;                        //正在执行任务的线程数
    atomic<int> liveNum;                        //存在线程池中的线程数
    atomic<int> exitNum;                        //需要关闭的线程数

    mutex poolmutex;                            //锁，用于保护线程池中的变量
    condition_variable notEmpty;                //传递信号

    atomic<bool> shutdown;                      //判断线程池是否需要销毁
};



