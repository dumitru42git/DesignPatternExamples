#pragma once

#include "binary_operation.h"

class BinaryDiv : public BinaryOperation
{
public:
    BinaryDiv(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
            : BinaryOperation(std::move(left), std::move(right))
    {
    }

    std::unique_ptr<Node> evaluate(Context& ctx) override
    {
        EvaluateResultCode unused;
        return evaluate(ctx, unused);
    }

    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code) override
    {
        auto div = [](auto left, auto right) -> std::unique_ptr<Value> { return std::make_unique<Value>(left / right); };

        return BinaryOperation::evaluate<BinaryDiv>(ctx, code, div);
    }

    void printInfo() const override { BinaryOperation::printInfo("BinaryDiv"); }

    std::string string() const override { return BinaryOperation::string("/"); }
};
