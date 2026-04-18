#pragma once

#include "../node.h"
#include "../operand.h"
#include "../operator.h"

#include <memory>
#include <print>

class BinaryPlusOperator : public BinaryOperator
{
public:
    BinaryPlusOperator(std::unique_ptr<Node> left, std::unique_ptr<Node> right);

    std::unique_ptr<Node> execute() override;
    std::unique_ptr<Node> accept(Node& op) override;
    std::unique_ptr<Node> visit(Value<int>& left) override;
    std::unique_ptr<Node> visit(Value<double>& left) override;
    void                  print() override;
};

namespace detail
{
    template<typename Left>
    class AddLeft : public Operator
    {
    public:
        AddLeft(Left left);

        std::unique_ptr<Node> execute() override;
        std::unique_ptr<Node> accept(Node&) override;
        std::unique_ptr<Node> visit(Value<int>& right) override;
        std::unique_ptr<Node> visit(Value<double>& right) override;
        void                  print() override;

    private:
        Left m_left;
    };

    template<typename Left, typename Right>
    class AddLeftRight : public Operator
    {
    public:
        AddLeftRight(Left left, Right right);

        std::unique_ptr<Node> execute() override;
        std::unique_ptr<Node> accept(Node& visitor) override;
        std::unique_ptr<Node> visit(Value<int>&) override;
        std::unique_ptr<Node> visit(Value<double>&) override;
        void                  print() override;

    public:
        Left  m_left;
        Right m_right;
    };
} // namespace detail

// Implementation
//
// BinaryPlusOperator

inline BinaryPlusOperator::BinaryPlusOperator(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : BinaryOperator(std::move(left), std::move(right))
{
}

inline std::unique_ptr<Node> BinaryPlusOperator::execute()
{
    auto addLeft      = m_left->accept(*this);
    auto addLeftRight = m_right->accept(*addLeft);
    return addLeftRight->execute();
}

inline std::unique_ptr<Node> BinaryPlusOperator::accept(Node& op)
{
    return execute()->accept(op);
}

inline std::unique_ptr<Node> BinaryPlusOperator::visit(Value<int>& left)
{
    return std::make_unique<detail::AddLeft<int>>(left.get());
}

inline std::unique_ptr<Node> BinaryPlusOperator::visit(Value<double>& left)
{
    return std::make_unique<detail::AddLeft<double>>(left.get());
}

inline void BinaryPlusOperator::print()
{
    std::println("BinaryPlusOperator");
}

// AddLeft

template<typename Left>
detail::AddLeft<Left>::AddLeft(Left left)
        : m_left{left}
{
}

template<typename Left>
std::unique_ptr<Node> detail::AddLeft<Left>::execute()
{
    return nullptr;
}

template<typename Left>
std::unique_ptr<Node> detail::AddLeft<Left>::accept(Node&)
{
    return nullptr;
}

template<typename Left>
std::unique_ptr<Node> detail::AddLeft<Left>::visit(Value<int>& right)
{
    return std::make_unique<AddLeftRight<Left, int>>(m_left, right.get());
}

template<typename Left>
std::unique_ptr<Node> detail::AddLeft<Left>::visit(Value<double>& right)
{
    return std::make_unique<AddLeftRight<Left, double>>(m_left, right.get());
}

template<typename Left>
void detail::AddLeft<Left>::print()
{
    std::println("detail::AddLeft<{}>", detail::TypeStringView<Left>());
}

// AddLeftRight

template<typename Left, typename Right>
detail::AddLeftRight<Left, Right>::AddLeftRight(Left left, Right right)
        : m_left{left}
        , m_right{right}
{
}

template<typename Left, typename Right>
std::unique_ptr<Node> detail::AddLeftRight<Left, Right>::execute()
{
    auto result  = m_left + m_right;
    using Result = decltype(result);

    if constexpr (std::same_as<Result, int>)
        return std::make_unique<Value<int>>(result);
    else if constexpr (std::same_as<Result, double>)
        return std::make_unique<Value<double>>(result);
    else
        static_assert(false, "Unsupported result type.");

    return nullptr;
}

template<typename Left, typename Right>
std::unique_ptr<Node> detail::AddLeftRight<Left, Right>::accept(Node&)
{
    return nullptr;
}

template<typename Left, typename Right>
std::unique_ptr<Node> detail::AddLeftRight<Left, Right>::visit(Value<int>&)
{
    return nullptr;
}

template<typename Left, typename Right>
std::unique_ptr<Node> detail::AddLeftRight<Left, Right>::visit(Value<double>&)
{
    return nullptr;
}

template<typename Left, typename Right>
void detail::AddLeftRight<Left, Right>::print()
{
    std::println("detail::AddLeftRight<{}, {}>", detail::TypeStringView<Left>(), detail::TypeStringView<Right>());
}
