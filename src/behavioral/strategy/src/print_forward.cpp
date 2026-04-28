#pragma once

#include "print_forward.h"

#include <print>

using namespace std::string_view_literals;

void PrintForward::operator_impl(ContainerVariant<std::vector, int, float> variant) const
{
    std::visit(PrintForward{}, variant);
}

void PrintForward::operator_impl(ContainerVariant<std::list, int, float> variant) const
{
    std::visit(PrintForward{}, variant);
}

template<std::ranges::range Container>
void PrintForward::operator()(std::reference_wrapper<Container> container)
{
    if (container.get().empty())
        return;

    auto it  = container.get().begin();
    auto end = container.get().end();

    std::print("{}", *it++);
    while (it != end)
        std::print(", {}", *it++);
    std::println();
}
