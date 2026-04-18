#pragma once

#include <print>

class Class
{
public:
    virtual void print(const int indent = 0, const int spaces = 4) const = 0
    {
        std::print("{: >{}}", "", indent * spaces);
    }

    virtual ~Class() = default;
};
