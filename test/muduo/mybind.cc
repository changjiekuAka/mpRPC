#include <iostream>
#include <thread>
#include <vector>
#include <functional>
using namespace std::placeholders;


class Thread
{
public:
    Thread(std::function<void(int)> func , int num) : _func(func),_num(num) {}
    std::thread Run()
    {
        std::thread t(_func,_num); //_func(_num)
        return t;
    }
private:
    std::function<void(int)> _func;
    int _num;
};

class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool() {
        for(int i = 0;i < workers.size();++i)
        {
            delete workers[i];
        }
    }

    void start(int size)
    {
        for(int i = 0; i < size; ++i)
        {
            workers.push_back(
                new Thread(std::bind(&ThreadPool::RunInThread,this,_1),i)
                );
        }
        for(int i = 0;i < size; ++i)
        {
            handlers.push_back(workers[i]->Run());
        }

        /*
        for(int i = 0;i < size; ++i)
        {
            handlers[i].join();
        }
        */

        for(std::thread& t:handlers)
        {
            t.join();
        }
    }

    
private:
    void RunInThread(int id)
    {
        std::cout << "call inThread id : " << id << std::endl;
    }
    std::vector<Thread*> workers;
    std::vector<std::thread> handlers;    
};

int main()
{
    ThreadPool threadpool;
    threadpool.start(10);

    return 0;
}