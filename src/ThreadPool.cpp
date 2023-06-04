#include "ThreadPool.h"

ThreadPool::ThreadPool(int min, int max)
{
    //初始化信息
    minNum = min;
    maxNum = max;
    busyNum = 0;
    liveNum = min;
    exitNum = 0;

    shutdown = false;

    //创建管理者线程
    managerID = thread(manager,this);

    //创建工作者线程
    for (int i = 0; i < min; i++)
    {
        workerIDs.emplace_back(thread(&worker, this));
    }
}

ThreadPool::~ThreadPool()
{
    //关闭线程池
    shutdown = true;

    notEmpty.notify_all();
    //回收管理者线程
    managerID.join();

    //回收用户线程
    for (thread& i : workerIDs)
    {
    i.join();
    }
}

int ThreadPool::getBusyNum()
{
    return busyNum;
}

int ThreadPool::getAliveNum()
{
    return liveNum;
}

void ThreadPool::addTask(function<void(int)> f,int arg)
{
    unique_lock<mutex> lock(poolmutex);
    tasks.push(Task(f,arg));

    //让一个工作线程开始工作
    notEmpty.notify_one();
}

void ThreadPool::worker(ThreadPool* pool)
{
    while (!pool->shutdown)
    {
        Task task;
        {
            unique_lock<mutex>lock(pool->poolmutex);
            
            //等待任务
            pool->notEmpty.wait(lock,[pool] { return pool->shutdown || !pool->tasks.empty(); });

            //线程池关闭
            if (pool->shutdown && pool->tasks.empty()){
                pool->liveNum--;
                return;
            }

            //线程池删除任务
            if (pool->exitNum > 0 && pool->liveNum > pool->minNum)
            {
                pool->exitNum --;
                pool->liveNum --;
                lock.unlock();
                pool->threadExit();
                return;
            }

            //从任务列表中取出任务
            task = move(pool->tasks.front());
            pool->tasks.pop();
        }

        //执行任务
        pool->busyNum++;
        task.f(task.arg);
        pool->busyNum--;
    }
}

void ThreadPool::manager(ThreadPool* pool)
{
    while (!pool->shutdown)
    {
        //3秒检测1次
        sleep(3);

        //取出线程池中的任务数与线程数，正在工作的线程数
        unique_lock<mutex>lock(pool->poolmutex);
        int queueSize = pool->tasks.size();
        lock.unlock();

        //添加线程，当任务列表任务过多时
        if(queueSize > pool->liveNum && pool->liveNum < pool->maxNum)
        {
            pool->liveNum++;
            pool->workerIDs.emplace_back(thread(&worker, pool));
        }

        //销毁线程,当空闲线程过多时
        if (pool->busyNum * 2 < pool->liveNum && pool->liveNum > pool->minNum)
        {
            pool->exitNum = 1;
            pool->notEmpty.notify_one();
        }
    }
}

void ThreadPool::threadExit()
{
    //获取本线程id
    thread::id t = this_thread::get_id();
    
    //从工作线程列表中删除本线程
    for (auto iter = workerIDs.begin(); iter != workerIDs.end(); iter++)
    {
        if (t == iter->get_id())
        {
            workerIDs.erase(iter);
            break;
        }
    }
}
