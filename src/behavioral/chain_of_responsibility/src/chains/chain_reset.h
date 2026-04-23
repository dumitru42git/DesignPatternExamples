#pragma once

#include "../chain.h"
#include "../object.h"

#include <print>

class ChainReset : public Chain
{
public:
    ChainReset(Chain* successor, Object& obj)
            : Chain(successor)
            , m_object{&obj}
    {
    }

    void handle(Request& request) override
    {
        if (request.type == Request::RESET)
        {
            const int value = 0;
            m_object->set(value);
            std::println("ChainReset: request = {}, m_object.set({})", request, value);
        }
        else
        {
            m_successor->handle(request);
        }
    }

private:
    Object* m_object;
};
