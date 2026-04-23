#pragma once

#include "binary_operation.h"

class BinaryPlus : public BinaryOperation
{
public:
    BinaryPlus(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
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
        auto plus = [](auto left, auto right) -> std::unique_ptr<Value> { return std::make_unique<Value>(left + right); };

        return BinaryOperation::evaluate<BinaryPlus>(ctx, code, plus);
    }

    void printInfo() const override { BinaryOperation::printInfo("BinaryPlus"); }

    std::string string() const override { return BinaryOperation::string("+"); }
};
