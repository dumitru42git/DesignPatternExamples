#pragma once

#include <atomic>
#include <chrono>
#include <mutex>
#include <print>
#include <thread>

using namespace std::chrono_literals;

inline void atomic_with_mutex()
{
    int              result = 0;
    std::mutex       mutex;
    std::atomic_bool check{};

    auto randomDuration = [](int min, int max) {
        std::random_device            rd;
        std::uniform_int_distribution distr(min, max);
        std::chrono::milliseconds     duration{distr(rd)};
        return duration;
    };

    auto expensiveOperation = [&]() {
        std::this_thread::sleep_for(randomDuration(10, 200));
        return 42;
    };

    auto printFirst = [&]() {
        std::println("Thread {:6}: entering", std::this_thread::get_id());
        std::this_thread::sleep_for(randomDuration(10, 200));

        if (!check.load(std::memory_order_acquire))
        {
            std::println("Thread {:6}: pass check 1", std::this_thread::get_id());

            std::scoped_lock lock(mutex);
            if (!check.load(std::memory_order_relaxed))
            {
                result = expensiveOperation();
                std::println("Thread {:6}: pass check 2, computed value = {}", std::this_thread::get_id(), result);

                check.store(true, std::memory_order_release);
            }
            else
            {
                std::println("Thread {:6}: fail check 2, value = {}", std::this_thread::get_id(), result);
            }
        }
        else
        {
            std::println("Thread {:6}: fail check 1, value = {}", std::this_thread::get_id(), result);
        }
    };

    std::println("--- atomic_with_mutex");
    {
        constexpr int             threadCount = 6;
        std::vector<std::jthread> threadVec;
        threadVec.reserve(threadCount);
        for (int i = 0; i < threadCount; ++i)
            threadVec.push_back(std::jthread(printFirst));
    }

    std::println();
}
