#pragma once

#include "node.h"
#include "operator.h"

#include <concepts>
#include <memory>
#include <print>

namespace detail
{
    template<typename T>
    consteval std::string_view TypeStringView()
    {
        if constexpr (std::same_as<T, int>)
            return "int";
        if constexpr (std::same_as<T, double>)
            return "double";

        return "unexpected type name";
    }
} // namespace detail

template<typename T>
class Value : public Node
{
public:
    Value(T value)
            : m_value{value}
    {
    }

    std::unique_ptr<Node> execute() override //
    {
        return nullptr;
    };

    std::unique_ptr<Node> accept(Node& op) override //
    {
        return static_cast<Operator&>(op).visit(*this);
    }

    void print() override //
    {
        std::println("Value<{}>: m_value = {}", detail::TypeStringView<T>(), m_value);
    }

    T get() const { return m_value; }

private:
    T m_value;
};
