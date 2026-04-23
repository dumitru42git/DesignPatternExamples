#pragma once

#include "../chain.h"
#include "../object.h"

class ChainPrintData : public Chain
{
public:
    ChainPrintData(Chain* successor, Object& obj)
            : Chain(successor)
            , m_object{&obj}
    {
    }

    void handle(Request& request) override
    {
        if (request.type == Request::PRINT)
        {
            std::println("ChainPrintData: request = {}, m_object.get() -> {}", request, m_object->get());
        }
        else
        {
            m_successor->handle(request);
        }
    }

private:
    Object* m_object;
};
