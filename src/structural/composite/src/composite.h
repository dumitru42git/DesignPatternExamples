#pragma once

#include "class.h"

#include <memory>
#include <print>
#include <vector>

class CompositeClass : public Class
{
public:
    CompositeClass(std::vector<std::unique_ptr<Class>> children)
            : m_children{std::move(children)}
    {
    }

    void print(const int indent = 0, const int spaces = 4) const override
    {
        Class::print(indent, spaces);
        std::println("CompositeClass:");
        for (auto& child : m_children)
        {
            child->print(indent + 1, spaces);
        }
    }

private:
    std::vector<std::unique_ptr<Class>> m_children;
};
