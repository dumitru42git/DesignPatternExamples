#pragma once

#include "../node.h"
#include "value.h"
#include "variable.h"

#include <format>
#include <memory>
#include <print>
#include <variant>

class UnaryOperation : public Node
{
public:
    using operand_type = std::variant<std::unique_ptr<Node>, std::unique_ptr<Variable>, std::unique_ptr<Value>>;

    UnaryOperation(std::unique_ptr<Node> operand)
            : m_operand{std::move(operand)}
    {
    }

    template<class Operation>
    std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code, auto operation)
    {
        auto overload1 = [&](std::unique_ptr<Value>& operand) -> std::unique_ptr<Node> //
        {
            code = EvaluateResultCode::EVALUATED;
            return std::visit(operation, operand->get());
        };

        auto overload2 = [&](auto& operand) -> std::unique_ptr<Node> {
            std::unique_ptr<Node> result;

            EvaluateResultCode    operandCode;
            std::unique_ptr<Node> operandEval = operand->evaluate(ctx, operandCode);

            if (operandCode == EvaluateResultCode::EVALUATED)
            {
                code = EvaluateResultCode::EVALUATED;
                std::unique_ptr<Value> operand(static_cast<Value*>(operandEval.release()));
                result = overload1(operand);
            }
            else
            {
                code   = EvaluateResultCode::UNEVALUATED;
                result = std::make_unique<Operation>(std::move(operandEval));
            }

            return result;
        };

        auto visitor = overloaded{overload1, overload2};
        return std::visit<std::unique_ptr<Node>>(visitor, m_operand);
    }

    void printInfo(std::string_view operationName) const
    {
        std::println("{}::m_operand = ({})",
                     operationName,
                     std::visit([](auto& node) { return node->string(); }, m_operand));
    }

    std::string string(std::string_view operationSymbol) const
    {
        return std::format("{}({})", operationSymbol, std::visit([](auto& node) { return node->string(); }, m_operand));
    }

private:
    operand_type m_operand;
};
