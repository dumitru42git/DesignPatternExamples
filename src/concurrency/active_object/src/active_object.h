#pragma once

#include <chrono>
#include <functional>
#include <future>
#include <mutex>
#include <print>
#include <queue>
#include <random>
#include <thread>

class ActiveObject
{
public:
    ActiveObject(const int multiplier)
            : m_multiplier{multiplier}
            , m_thread([this](std::stop_token stopToken) { run(stopToken); })
    {
    }

    void work(const int threadNum, const int value)
    {
        auto function = [this, threadNum, value]() { task(threadNum, value); };

        {
            std::scoped_lock lock(m_mutex);
            m_tasks.push(function);
        }
        m_cv.notify_one();
    }

    std::future<int> futureWork(const int threadNum, const int value)
    {
        std::packaged_task<int()> task([this, threadNum, value]() { return task(threadNum, value); });

        auto future   = task.get_future();
        auto function = [task = std::move(task)]() mutable { task(); };

        {
            std::scoped_lock lock(m_mutex);
            m_tasks.push(std::move(function));
        }
        m_cv.notify_one();

        return future;
    }

private:
    int task(const int threadNum, const int value) const
    {
        std::random_device            rd;
        std::uniform_int_distribution distr(200, 500);
        std::chrono::milliseconds     sleepDuration{distr(rd)};

        std::this_thread::sleep_for(sleepDuration);

        std::println("---Task done in {}:", sleepDuration);
        std::println("    thread = {}, result = {}, value = {}", threadNum, value * m_multiplier, value);
        return value * m_multiplier;
    }

private:
    void run(std::stop_token stopToken)
    {
        while (true)
        {
            std::move_only_function<void()> task;

            std::unique_lock lock(m_mutex);
            const bool       hasTasks = m_cv.wait(lock, stopToken, [this]() { return !m_tasks.empty(); });

            if (hasTasks)
            {
                task = std::move(m_tasks.front());
                m_tasks.pop();

                lock.unlock();
                task();
            }
            else
            {
                return;
            }
        }
    }

    std::mutex                                  m_mutex;
    std::condition_variable_any                 m_cv;
    std::queue<std::move_only_function<void()>> m_tasks;
    int                                         m_multiplier;
    std::jthread                                m_thread; // Destroyed first
};
