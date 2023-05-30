#include <queue>
#include <mutex>
#include <pthread.h>
#include <vector>

using namespace std;
using Fun = void (*)(void *arg);

struct Task
{
    Fun function;
    void *arg;
    Task();
    Task(Fun f, void* arg);
};

class TaskQueue
{
private:
    queue<Task> taskque;
    mutex m_mutex;
public:
    TaskQueue(){};
    ~TaskQueue(){};

    void addTask(Task task);
    void addTask(Fun f,void* arg);

    Task takeTask();

    inline int taskNum(){
        return taskque.size();
    }
};

class ThreadPool
{
private:
    TaskQueue taskq;                  //

    pthread_t managerIDs;
    vector<pthread_t> threadIDs;

    int minNum;
    int maxNUm;
    int busyNum;
    int liveNum;
    int exitNum;

    mutex poolmutex;
    pthread_cond_t notEmpty;

    bool shutdown;

public:
    ThreadPool(/* args */);
    ~ThreadPool();
};


