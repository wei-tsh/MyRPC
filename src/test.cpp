#include"ThreadPool.h"
#include<iostream>

void test(int a = 55){
    cout<<a<<endl;
}

int main(int argc, char const *argv[])
{
    ThreadPool pool(4,10);
    
    for (int i = 0; i < 100; i++)
    {
        int a = i;
        pool.addTask(test,a);
    }

    sleep(1);
}
