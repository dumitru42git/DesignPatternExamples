#pragma once

#include "../node.h"
#include "value.h"

#include <format>
#include <memory>
#include <print>
#include <variant>

class UnaryOperation : public Node
{
public:
    UnaryOperation(std::unique_ptr<Node> operand)
            : m_operand{std::move(operand)}
    {
    }

    template<class OperationClass>
    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code, auto operationVisitor)
    {
        std::unique_ptr<Node> result;

        EvaluateResultCode    operandCode;
        std::unique_ptr<Node> operandEval = m_operand->evaluate(ctx, operandCode);

        if (operandCode == EvaluateResultCode::EVALUATED)
        {
            code = EvaluateResultCode::EVALUATED;
            std::unique_ptr<Value> operand(static_cast<Value*>(operandEval.release()));
            result = std::visit(operationVisitor, operand->get());
        }
        else
        {
            code   = EvaluateResultCode::UNEVALUATED;
            result = std::make_unique<OperationClass>(std::move(operandEval));
        }

        return result;
    }

    void printInfo(std::string_view operationName) const
    {
        std::println("{}::m_operand = {}", operationName, m_operand->string());
    }

    std::string string(std::string_view operationSymbol) const
    {
        return std::format("({}{})", operationSymbol, m_operand->string());
    }

private:
    std::unique_ptr<Node> m_operand;
};
