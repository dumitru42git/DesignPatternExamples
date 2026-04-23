#pragma once
#include "request.h"

#include <print>

class Chain
{
public:
    virtual void handle(Request& request) { std::println("Chain: request = {} unhandled", request); };

    virtual ~Chain() = default;

protected:
    Chain(Chain* successor)
            : m_successor{successor ? successor : baseChain()}
    {
    }

private:
    Chain() = default;
    Chain* baseChain() const
    {
        static Chain baseChainInstance;
        return &baseChainInstance;
    }

protected:
    Chain* m_successor{};
};
