#pragma once

#include "state_visitor.h"

#include <memory>

class State
{
public:
    virtual ~State() = default;

    virtual void                                 accept(StateVisitor& visitor) = 0;
    virtual [[nodiscard]] std::unique_ptr<State> update()                      = 0;
    virtual void                                 print() const                 = 0;
};
