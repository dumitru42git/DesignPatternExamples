#include "state_initializing.h"
//
#include "state_ready.h"

#include <chrono>
#include <print>
#include <random>

using namespace std::chrono_literals;

StateInitializing::StateInitializing()
{
    m_future = std::async(
        std::launch::async,
        [](std::stop_token stopToken) //
        {
            std::println("---StateInitializing -> lauched async computation");
            std::optional<int> result;

            std::random_device                  rd;
            std::chrono::steady_clock::duration elapsed{};

            int sum = 40;
            while (elapsed < 700ms)
            {
                const auto start = std::chrono::steady_clock::now();

                if (stopToken.stop_requested())
                    return result; // nullopt

                std::this_thread::sleep_for(300ms + std::chrono::milliseconds{rd() % 200});
                ++sum;

                const auto end       = std::chrono::steady_clock::now();
                auto       duration  = end - start;
                elapsed             += duration;
            }

            result = sum;
            return result;
        },
        m_stopSource.get_token());
}

void StateInitializing::accept(StateVisitor& rawVisitor)
{
    auto* visitor = dynamic_cast<StateVisitorT<StateInitializing>*>(&rawVisitor);
    if (visitor)
    {
        visitor->visit(*this);
    }
    else
    {
        std::println("---StateInitializing: class {} does not implement visitor", rawVisitor.visitorName());
    }
}

std::unique_ptr<State> StateInitializing::update()
{
    if (m_future.valid())
    {
        auto status = m_future.wait_for(0s);
        if (status == std::future_status::ready)
        {
            if (!m_stopSource.stop_requested())
            {
                std::println("---StateInitializing -> async computation finished");
                m_compResult = m_future.get();
            }
        }
        if (m_stopSource.stop_requested())
        {
            std::println("---StateInitializing -> async computation skipped");
            m_compResult = -1;
        }
    }

    std::unique_ptr<State> nextState{nullptr};
    if (m_compResult.has_value())
        nextState = std::make_unique<StateReady>(m_compResult.value());

    print();

    return nextState;
}

void StateInitializing::print() const
{
    if (m_compResult.has_value())
        std::println("---StateInitializing: compResult = {}, stopRequested = {}",
                     m_compResult.value(),
                     m_stopSource.stop_requested());
    else
        std::println("---StateInitializing: compResult = nullopt, stopRequested = {}", m_stopSource.stop_requested());
}

void StateInitializing::skipComputation()
{
    m_stopSource.request_stop();
}
