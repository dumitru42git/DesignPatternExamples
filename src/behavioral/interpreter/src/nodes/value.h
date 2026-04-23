#pragma once

#include "../node.h"

#include <memory>
#include <print>
#include <string_view>
#include <variant>

class Context;

class Value : public Node
{
public:
    Value(auto value)
            : m_value(value)
    {
    }

    Value() = default;

    using value_type = std::variant<int, double>;

public:
    std::unique_ptr<Node> evaluate(Context& ctx) override //
    {
        return std::make_unique<Value>(*this);
    }

    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code) override //
    {
        code = EvaluateResultCode::EVALUATED;
        return std::make_unique<Value>(*this);
    }

    void printInfo() const override
    {
        std::visit(
            [](auto& value) {
                std::println("Value::m_value = {} ({})", //
                             value,
                             valueTypeName<decltype(value)>());
            },
            m_value);
    }

    std::string string() const override
    {
        return std::visit([](auto& value) { return std::to_string(value); }, m_value);
    }

public:
    value_type get() const //
    {
        return m_value;
    }

private:
    template<typename T>
    static consteval std::string_view valueTypeName()
    {
        using Type = std::remove_cvref_t<T>;
        if constexpr (std::same_as<Type, int>)
            return "int";
        if constexpr (std::same_as<Type, double>)
            return "double";
        return "unknown type";
    }

private:
    value_type m_value{};
};
