#pragma once

#include <string_view>

class StateVisitor
{
public:
    virtual ~StateVisitor() = default;

    constexpr virtual std::string_view visitorName() const = 0;
};

template<typename StateT>
class StateVisitorT
{
public:
    virtual ~StateVisitorT() = default;

    virtual void visit(StateT& state) = 0;
};
