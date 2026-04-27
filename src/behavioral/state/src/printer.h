#pragma once

#include "state.h"
#include "state_visitor.h"

#include <memory>

class Printer
{
public:
    Printer(std::unique_ptr<State> state, std::unique_ptr<StateVisitor> stateVisitor);
    virtual ~Printer() = default;

    virtual void print() = 0;

protected:
    std::unique_ptr<State>        m_state;
    std::unique_ptr<StateVisitor> m_stateVisitor;
};
