#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <print>
#include <queue>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

class ThreadPool
{
    using Task = std::function<void()>;

public:
    ThreadPool(const int count, bool delayStart = false, bool finishQueueOnDestructor = false)
            : m_finishQueueOnDestructor{finishQueueOnDestructor}
    {
        m_threads.reserve(count);
        if (!delayStart)
        {
            const auto stopToken = m_stopSource.get_token();
            for (int i = 0; i < count; ++i)
            {
                m_threads.emplace_back(*this, stopToken);
            }
        }
    }

    ~ThreadPool()
    {
        if (m_finishQueueOnDestructor && !m_threads.empty())
        {
            std::unique_lock lock(m_queueMutex);
            m_destructorCv.wait(lock, [this]() { return m_taskQueue.empty(); });
        }

        m_stopSource.request_stop();

        for (auto& thread : m_threads)
        {
            thread.join();
        }
    }

    void start()
    {
        if (m_threads.empty())
        {
            const auto stopToken = m_stopSource.get_token();
            const int  count     = m_threads.capacity();
            for (int i = 0; i < count; ++i)
            {
                m_threads.emplace_back(*this, stopToken);
            }
        }
    }

    void push(Task task)
    {
        {
            std::scoped_lock lock(m_queueMutex);
            m_taskQueue.push(std::move(task));
        }
        m_popCv.notify_one();
    }

private:
    Task pop()
    {
        Task             task;
        std::unique_lock lock(m_queueMutex);

        if (m_popCv.wait_for(lock, 10ms, [this]() { return !m_taskQueue.empty(); }))
        {
            task = std::move(m_taskQueue.front());
            m_taskQueue.pop();
            lock.unlock();

            if (m_finishQueueOnDestructor)
            {
                m_destructorCv.notify_one();
            }
        }

        return task;
    }

private:
    class Thread
    {
    public:
        Thread(ThreadPool& pool, std::stop_token stopToken)
                : m_pool{pool}
                , m_thread([this, stopToken]() { run(stopToken); })
        {
        }

        void join()
        {
            if (m_thread.joinable())
            {
                m_thread.join();
            }
        }

    private:
        void run(std::stop_token stopToken)
        {
            std::println("Thread {} started", std::this_thread::get_id());
            while (!stopToken.stop_requested())
            {
                Task task = m_pool.pop();
                if (task)
                {
                    task();
                }
                else
                {
                    std::println("Thread {} stalling", std::this_thread::get_id());
                }
            }
            std::println("Thread {} exited", std::this_thread::get_id());
        }

    private:
        ThreadPool& m_pool;
        std::thread m_thread;
    };

private:
    std::mutex              m_queueMutex;
    std::condition_variable m_destructorCv;
    std::condition_variable m_popCv;
    std::queue<Task>        m_taskQueue;
    std::stop_source        m_stopSource;
    std::vector<Thread>     m_threads;
    bool                    m_finishQueueOnDestructor;
};
