#pragma once

#include "../node.h"
#include "../operand.h"
#include "../operator.h"

#include <memory>
#include <print>

class UnaryMinusOperator : public UnaryOperator
{
public:
    UnaryMinusOperator(std::unique_ptr<Node> node)
            : UnaryOperator(std::move(node))
    {
    }

    std::unique_ptr<Node> execute() override { return m_node->accept(*this); }

    std::unique_ptr<Node> accept(Node& op) override { return execute()->accept(op); }

    std::unique_ptr<Node> visit(Value<int>& value) override //
    {
        return std::make_unique<Value<int>>(-value.get());
    }

    std::unique_ptr<Node> visit(Value<double>& value) override //
    {
        return std::make_unique<Value<double>>(-value.get());
    }

    void print() override { std::println("UnaryMinusOperator"); }
};
