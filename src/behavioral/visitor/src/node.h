#pragma once

#include <memory>

class Node
{
public:
    virtual std::unique_ptr<Node> execute()             = 0;
    virtual std::unique_ptr<Node> accept(Node& visitor) = 0;
    virtual void                  print()               = 0;

    virtual ~Node() = default;
};
