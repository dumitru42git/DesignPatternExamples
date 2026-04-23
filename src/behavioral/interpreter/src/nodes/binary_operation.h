#pragma once

#include "../node.h"
#include "value.h"
#include "variable.h"

#include <format>
#include <memory>
#include <print>
#include <variant>

class BinaryOperation : public Node
{
public:
    using operand_type = std::variant<std::unique_ptr<Node>, std::unique_ptr<Variable>, std::unique_ptr<Value>>;

    BinaryOperation(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
            : m_left{std::move(left)}
            , m_right{std::move(right)}
    {
    }

    template<class Operation>
    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code, auto operation)
    {
        auto overload1 = [&](std::unique_ptr<Value>& lhs,
                             std::unique_ptr<Value>& rhs) -> std::unique_ptr<Node> //
        {
            code = EvaluateResultCode::EVALUATED;
            return std::visit(operation, lhs->get(), rhs->get());
        };

        auto overload2 = [&](auto& lhs, auto& rhs) -> std::unique_ptr<Node> {
            std::unique_ptr<Node> result;

            EvaluateResultCode    lhsCode;
            std::unique_ptr<Node> lhsEval = lhs->evaluate(ctx, lhsCode);

            EvaluateResultCode    rhsCode;
            std::unique_ptr<Node> rhsEval = rhs->evaluate(ctx, rhsCode);

            if (lhsCode == EvaluateResultCode::EVALUATED && rhsCode == EvaluateResultCode::EVALUATED)
            {
                code = EvaluateResultCode::EVALUATED;
                std::unique_ptr<Value> lhs(static_cast<Value*>(lhsEval.release()));
                std::unique_ptr<Value> rhs(static_cast<Value*>(rhsEval.release()));
                result = overload1(lhs, rhs);
            }
            else
            {
                code   = EvaluateResultCode::UNEVALUATED;
                result = std::make_unique<Operation>(std::move(lhsEval), std::move(rhsEval));
            }

            return result;
        };

        auto visitor = overloaded{overload1, overload2};
        return std::visit<std::unique_ptr<Node>>(visitor, m_left, m_right);
    }

    void printInfo(std::string_view operationName) const
    {
        std::println("{}::m_left = ({}), {}::m_right = ({})",
                     operationName,
                     std::visit([](auto& node) { return node->string(); }, m_left),
                     operationName,
                     std::visit([](auto& node) { return node->string(); }, m_right));
    }

    std::string string(std::string_view operationSymbol) const
    {
        return std::format("({}) {} ({})",
                           std::visit([](auto& node) { return node->string(); }, m_left),
                           operationSymbol,
                           std::visit([](auto& node) { return node->string(); }, m_right));
    }

private:
    operand_type m_left;
    operand_type m_right;
};
