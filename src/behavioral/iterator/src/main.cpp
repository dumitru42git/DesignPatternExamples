#include "iterable.h"

#include <concepts>
#include <iterator>
#include <print>

template<typename T>
    requires std::forward_iterator<typename T::iterator_type>
void PrintElements(const T& container)
{
    for (const auto& el : container)
    {
        std::print("{} ", el);
    }
    std::println();
}

int main()
{
    std::println("---Iterator Pattern---");

    ForwardIterable<int, 10> container{23, 43, 3, 84};
    PrintElements(container);

    return 0;
}
