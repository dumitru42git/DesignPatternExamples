#include "state_finished.h"
//
#include "state_initializing.h"

#include <print>

void StateFinished::accept(StateVisitor& rawVisitor)
{
    auto* visitor = dynamic_cast<StateVisitorT<StateFinished>*>(&rawVisitor);
    if (visitor)
    {
        visitor->visit(*this);
    }
    else
    {
        std::println("---StateFinished: class {} does not implement visitor", rawVisitor.visitorName());
    }
}

std::unique_ptr<State> StateFinished::update()
{
    std::unique_ptr<State> nextState{nullptr};
    if (m_shouldRestart)
        nextState = std::make_unique<StateInitializing>();

    print();

    return nextState;
}

void StateFinished::print() const
{
    std::println("---StateFinished: shouldRestart = {}", m_shouldRestart);
}

void StateFinished::restart()
{
    m_shouldRestart = true;
}
