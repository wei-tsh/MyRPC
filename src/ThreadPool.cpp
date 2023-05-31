#pragma once
#include "ThreadPool.h"

ThreadPool::ThreadPool(int min, int max)
{
    minNum = min;
    maxNum = max;
    busyNum = 0;
    liveNum = min;
    exitNum = 0;

    shutdown = false;
    managerID = thread(manager,this);
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

template<class F, class... Args>
future<typename result_of<F()>::type> ThreadPool::addTask(F&& f, Args&&... args)
{
    using return_type = result_of<F()>::type;

    auto task = make_shared<packaged_task<return_type()> >(bind(forward<F>(f), forward<Args>(args)...));

    future<return_type> result = task->get_future();
    {
        unique_lock<mutex> lock(poolmutex);

        tasks.emplace([task]() { (*task)(); });
    }

    notEmpty.notify_one();
    return result;
}

void ThreadPool::worker(ThreadPool* pool)
{
    while (!pool->shutdown)
    {
        function<void()> task;
        {
            unique_lock<mutex>lock(pool->poolmutex);
            pool->notEmpty.wait(lock,[pool] { return pool->shutdown || !pool->tasks.empty(); });

            if (pool->shutdown && pool->tasks.empty()){
                pool->liveNum--;
                return;
            }
            
            if (pool->exitNum > 0 && pool->liveNum > pool->minNum)
            {
                pool->exitNum --;
                pool->liveNum --;
                lock.unlock();
                pool->threadExit();
                return;
            }

            task = move(pool->tasks.front());
            pool->tasks.pop();
        }
        pool->busyNum++;
        task();
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

        //添加线程，但任务列表任务过多时
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
    thread::id t = this_thread::get_id();

    for (auto iter = workerIDs.begin(); iter != workerIDs.end(); iter++)
    {
        if (t == iter->get_id())
        {
            workerIDs.erase(iter);
            break;
        }
    }
}
