#include "thread.h"

#include <print>
#include <random>

void printTask(int taskNum)
{
    std::random_device            rd;
    std::uniform_int_distribution distr(10, 1000);
    std::chrono::milliseconds     sleepDuration{distr(rd)};

    std::this_thread::sleep_for(sleepDuration);

    std::println("Task {}, thread_id = {}, duration = {}", taskNum, std::this_thread::get_id(), sleepDuration);
}

int main()
{
    std::println("---Thread Pool Pattern---");

    std::println();
    {
        bool       delayStart              = true;
        bool       finishQueueOnDestructor = false;
        ThreadPool threadPool(2, delayStart, finishQueueOnDestructor);

        threadPool.push([]() { printTask(1); });
        threadPool.push([]() { printTask(2); });
        threadPool.push([]() { printTask(3); });

        threadPool.start();
    }

    std::println();
    {
        bool       delayStart              = true;
        bool       finishQueueOnDestructor = false;
        ThreadPool threadPool(2, delayStart, finishQueueOnDestructor);

        threadPool.push([]() { printTask(1); });
        threadPool.push([]() { printTask(2); });
        threadPool.push([]() { printTask(3); });

        threadPool.start();
        std::this_thread::sleep_for(1000ms);
    }

    std::println();
    {
        bool       delayStart              = false;
        bool       finishQueueOnDestructor = true;
        ThreadPool threadPool(4, delayStart, finishQueueOnDestructor);

        threadPool.push([]() { printTask(1); });
        threadPool.push([]() { printTask(2); });
        threadPool.push([]() { printTask(3); });
    }

    return 0;
}
