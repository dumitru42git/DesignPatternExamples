#include "active_object.h"

#include <chrono>
#include <print>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

int main()
{
    std::println("---Active Object Pattern---");
    std::println();

    constexpr int multiplier = 2;
    ActiveObject  object(multiplier);

    auto doWork = [&](int threadNum) {
        std::vector<std::future<int>> futures;

        for (int i = 0; i < 10; ++i)
        {
            const int value = i + threadNum;
            if (value % 2)
                object.work(threadNum, value);
            else
                futures.push_back(object.futureWork(threadNum, value));
        }

        while (!futures.empty())
        {
            std::erase_if(futures, [&](std::future<int>& future) {
                const bool isValid = future.valid();
                if (isValid)
                {
                    auto status = future.wait_for(0ms);
                    if (status == std::future_status::ready)
                    {
                        // Can interleave with print in tasks
                        const auto result = future.get();
                        std::println("[Future ready: thread = {}, result = {}]", threadNum, result);
                    }
                }
                return !isValid;
            });
            std::this_thread::sleep_for(20ms);
        }
    };

    std::jthread th1(doWork, 10);
    std::jthread th2(doWork, 20);

    return 0;
}
