#pragma once

#include "unary_operation.h"

class UnaryMinus : public UnaryOperation
{
public:
    UnaryMinus(std::unique_ptr<Node> operand)
            : UnaryOperation(std::move(operand))
    {
    }

    std::unique_ptr<Node> evaluate(Context& ctx) override
    {
        EvaluateResultCode unused;
        return evaluate(ctx, unused);
    }

    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code) override
    {
        auto minus = [](auto operand) -> std::unique_ptr<Node> { return std::make_unique<Value>(-operand); };

        return UnaryOperation::evaluate<UnaryMinus>(ctx, code, minus);
    }

    void printInfo() const override { UnaryOperation::printInfo("UnaryMinus"); }

    std::string string() const override { return UnaryOperation::string("-"); }
};
