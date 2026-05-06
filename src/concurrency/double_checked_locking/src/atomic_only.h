#pragma once

#include <atomic>
#include <chrono>
#include <format>
#include <print>
#include <random>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

inline void atomic_only()
{
    constexpr int   uninitialized_value = -1;
    std::atomic_int atomicVar           = uninitialized_value;

    auto randomDuration = [](int min, int max) {
        std::random_device            rd;
        std::uniform_int_distribution distr(min, max);
        std::chrono::milliseconds     duration{distr(rd)};
        return duration;
    };

    auto expensiveOperation = [&]() {
        std::this_thread::sleep_for(randomDuration(10, 200));
        return std::stoi(std::format("{}", std::this_thread::get_id())) + 42;
    };

    auto printFirst = [&]() {
        std::println("Thread {:6}: entering", std::this_thread::get_id());
        std::this_thread::sleep_for(randomDuration(10, 200));

        auto value = atomicVar.load(std::memory_order_acquire);
        if (value == uninitialized_value)
        {
            std::println("Thread {:6}: pass check 1", std::this_thread::get_id());
            int computedValue = expensiveOperation();

            int expected = uninitialized_value;
            if (atomicVar.compare_exchange_strong(expected,
                                                  computedValue,
                                                  std::memory_order_acq_rel,
                                                  std::memory_order_acquire))
            {
                std::println("Thread {:6}: pass check 2, stored value = {}", std::this_thread::get_id(), computedValue);
            }
            else
            {
                std::println("Thread {:6}: fail check 2, discarding = {}, value = {}",
                             std::this_thread::get_id(),
                             computedValue,
                             expected);
            }
        }
        else
        {
            std::println("Thread {:6}: fail check 1, value = {}", std::this_thread::get_id(), value);
        }
    };

    std::println("--- atomic_only");
    {
        constexpr int             threadCount = 6;
        std::vector<std::jthread> threadVec;
        threadVec.reserve(threadCount);
        for (int i = 0; i < threadCount; ++i)
            threadVec.push_back(std::jthread(printFirst));
    }

    std::println();
}
