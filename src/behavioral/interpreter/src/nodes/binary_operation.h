#pragma once

#include "../node.h"
#include "value.h"

#include <format>
#include <memory>
#include <print>
#include <variant>

class BinaryOperation : public Node
{
public:
    BinaryOperation(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
            : m_left{std::move(left)}
            , m_right{std::move(right)}
    {
    }

    template<class OperationClass>
    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code, auto operationVisitor)
    {
        std::unique_ptr<Node> result;

        EvaluateResultCode    lhsCode, rhsCode;
        std::unique_ptr<Node> lhsEval = m_left->evaluate(ctx, lhsCode);
        std::unique_ptr<Node> rhsEval = m_right->evaluate(ctx, rhsCode);

        if (lhsCode == EvaluateResultCode::EVALUATED && rhsCode == EvaluateResultCode::EVALUATED)
        {
            code = EvaluateResultCode::EVALUATED;
            std::unique_ptr<Value> lhs(static_cast<Value*>(lhsEval.release()));
            std::unique_ptr<Value> rhs(static_cast<Value*>(rhsEval.release()));
            result = std::visit(operationVisitor, lhs->get(), rhs->get());
        }
        else
        {
            code   = EvaluateResultCode::UNEVALUATED;
            result = std::make_unique<OperationClass>(std::move(lhsEval), std::move(rhsEval));
        }

        return result;
    }

    void printInfo(std::string_view operationName) const
    {
        std::println("{}::m_left = {}, {}::m_right = {}", operationName, m_left->string(), operationName, m_right->string());
    }

    std::string string(std::string_view operationSymbol) const
    {
        return std::format("({} {} {})", m_left->string(), operationSymbol, m_right->string());
    }

private:
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
};
