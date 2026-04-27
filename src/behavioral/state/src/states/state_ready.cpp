#include "state_ready.h"
//
#include "state_finished.h"

#include <print>

StateReady::StateReady(const int value)
        : m_value{value}
        , m_count{0}
        , m_index{0}
        , m_shouldStop{false}
{
}

void StateReady::init(int count)
{
    m_count = count;
}

void StateReady::init(int count, StateVisitor& visitor)
{
    std::println("---StateReady: {} visitor -> StateReady::init(): count = {}", visitor.visitorName(), count);
    init(count);
}

void StateReady::accept(StateVisitor& rawVisitor)
{
    auto* visitor = dynamic_cast<StateVisitorT<StateReady>*>(&rawVisitor);
    if (visitor)
    {
        visitor->visit(*this);
    }
    else
    {
        std::println("---StateReady: class {} does not implement visitor", rawVisitor.visitorName());
    }
}

std::unique_ptr<State> StateReady::update()
{
    std::unique_ptr<State> nextState{nullptr};
    if (!m_shouldStop)
    {
        if (m_index < m_count)
        {
            ++m_value;
            ++m_index;
        }

        if (m_index >= m_count)
            stop();
    }
    if (m_shouldStop)
    {
        nextState = std::make_unique<StateFinished>();
    }

    print();

    return nextState;
}

void StateReady::print() const
{
    std::println("---StateReady: value = {}, count = {}, index = {}, shouldStop = {}",
                 m_value,
                 m_count,
                 m_index,
                 m_shouldStop);
}

void StateReady::stop()
{
    m_shouldStop = true;
}

int StateReady::value() const
{
    return m_value;
}
