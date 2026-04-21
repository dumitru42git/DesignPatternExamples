#pragma once

#include "classA.h"
#include "classB.h"
#include "classC.h"

#include <random>

class Facade
{
public:
    int run()
    {
        std::random_device            rd;
        std::mt19937_64               mt(rd());
        std::uniform_int_distribution uintd(0, 10);
        int                           seed = uintd(mt);

        std::optional<int> a = m_a.run(seed);
        if (a.has_value())
        {
            int b = m_b.run(a.value());
            int c = m_c.run(a.value() + b);
            return c;
        }
        else
        {
            int b = m_b.run(-seed);
            int c = m_c.run(2 * b);
            return b + c;
        }
    }

private:
    ClassA m_a;
    ClassB m_b;
    ClassC m_c;
};
