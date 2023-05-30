#include "ThreadPool.h"

Task::Task(){
    function = nullptr;
    arg = nullptr;
}

Task::Task(Fun f, void* arg)
{
    this->arg = arg;
    function = f;
}

void TaskQueue::addTask(Task task)
{
    lock_guard<mutex> lock(m_mutex);
    taskque.push(task);
}

void TaskQueue::addTask(Fun f, void *arg)
{
    lock_guard<mutex> lock(m_mutex);
    taskque.push(Task(f,arg));
}

Task TaskQueue::takeTask()
{
    Task t;
    lock_guard<mutex> lock(m_mutex);
    if (!taskque.empty())
    {
        t = taskque.front();
        taskque.pop();
    }
    return t;
}
