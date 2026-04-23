#pragma once

#include "../node.h"
#include "value.h"

#include <expected>
#include <string>

class Variable : public Node
{
public:
    Variable(std::string name)
            : m_name{std::move(name)}
    {
    }

public:
    std::unique_ptr<Node> evaluate(Context& ctx) override
    {
        EvaluateResultCode unused;
        return evaluate(ctx, unused);
    }

    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code) override
    {
        std::unique_ptr<Node> node;

        auto value = ctx.get(m_name);
        if (value.has_value())
        {
            node = std::make_unique<Value>(value.value());
            code = EvaluateResultCode::EVALUATED;
        }
        else
        {
            node = std::make_unique<Variable>(*this);
            code = EvaluateResultCode::UNEVALUATED;
        }

        return node;
    }

    void printInfo() const override { std::println("Variable::m_name = {}", m_name); }

    std::string string() const override { return m_name; }

private:
    std::string m_name;
};
