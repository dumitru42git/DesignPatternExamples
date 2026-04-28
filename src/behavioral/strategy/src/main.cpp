#include "class.h"
#include "print_forward.h"
#include "print_reverse.h"

#include <print>

template<typename PrintStrategy>
Class makeObject()
{
    return Class(std::vector<int>{1, 2, 3},
                 std::vector<double>{11.1, 22.2, 33.3},
                 std::list<float>{111.1f, 222.2f, 333.3f},
                 std::set<int>{7, 8, 9},
                 std::make_unique<PrintStrategy>());
}

template<typename PrintStrategy>
constexpr ConstexprClass makeConstObject()
{
    return ConstexprClass(std::vector<int>{1, 2, 3},
                          std::vector<double>{1.1, 2.2, 3.3},
                          std::make_unique<PrintStrategy>());
}

constexpr int constexprMain()
{
    ConstexprClass constexprObjectForward = makeConstObject<PrintForward>();
    ConstexprClass constexprObjectReverse = makeConstObject<PrintReverse>();

    constexprObjectForward.print();
    constexprObjectReverse.print();

    return 0;
}

int main()
{
    std::println("---Strategy Pattern---");
    std::println();

    constexpr int unused = constexprMain();

    {
        ConstexprClass constexprObjectForward = makeConstObject<PrintForward>();
        ConstexprClass constexprObjectReverse = makeConstObject<PrintReverse>();

        constexprObjectForward.print();
        std::println();
        constexprObjectReverse.print();
        std::println();
    }
    std::println("----------------------------");
    std::println();
    {
        Class objectForward = makeObject<PrintForward>();
        Class objectReverse = makeObject<PrintReverse>();

        objectForward.print();
        std::println();
        objectReverse.print();
        std::println();
    }

    return 0;
}
