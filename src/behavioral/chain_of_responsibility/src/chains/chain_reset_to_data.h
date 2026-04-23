#pragma once

#include "../chain.h"
#include "../object.h"

class ChainResetToData : public Chain
{
public:
    ChainResetToData(Chain* successor, Object& obj)
            : Chain(successor)
            , m_object{&obj}
    {
    }

    void handle(Request& request) override
    {
        if (request.type == Request::RESET)
        {
            std::println("ChainResetToData: request = {}, m_object.set({})", request, request.data);
            m_object->set(request.data);
        }
        else
        {
            m_successor->handle(request);
        }
    }

private:
    Object* m_object;
};
