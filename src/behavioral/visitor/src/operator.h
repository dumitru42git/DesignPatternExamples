#pragma once

#include "node.h"

#include <memory>

template<typename>
class Value;

class Operator : public Node
{
public:
    virtual std::unique_ptr<Node> visit(Value<int>& value)   = 0;
    virtual std::unique_ptr<Node> visit(Value<double>& value) = 0;
};

class UnaryOperator : public Operator
{
public:
    UnaryOperator(std::unique_ptr<Node> node)
            : m_node(std::move(node))
    {
    }

protected:
    std::unique_ptr<Node> m_node;
};

class BinaryOperator : public Operator
{
public:
    BinaryOperator(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
            : m_left(std::move(left))
            , m_right(std::move(right))
    {
    }

protected:
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;
};
