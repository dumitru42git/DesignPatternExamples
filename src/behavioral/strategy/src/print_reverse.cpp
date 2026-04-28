#include "print_reverse.h"

#include <print>

void PrintReverse::operator_impl(ContainerVariant<std::vector, int, float> variant) const
{
    std::visit(PrintReverse{}, variant);
}

template<std::ranges::range Container>
void PrintReverse::operator()(std::reference_wrapper<Container> container)
{
    if (container.get().empty())
        return;

    auto it  = container.get().rbegin();
    auto end = container.get().rend();

    std::print("{}", *it++);
    while (it != end)
        std::print(", {}", *it++);
    std::println();
}
