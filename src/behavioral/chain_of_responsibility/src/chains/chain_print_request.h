#pragma once

#include "../chain.h"

class ChainPrintRequest : public Chain
{
public:
    ChainPrintRequest(Chain* successor)
            : Chain(successor)
    {
    }

    void handle(Request& request) override
    {
        if (request.type == Request::PRINT)
        {
            std::println("ChainPrintRequest: request = {} printed", request);
        }
        else
        {
            m_successor->handle(request);
        }
    }
};
