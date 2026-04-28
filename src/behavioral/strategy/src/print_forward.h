#pragma once

#include "print.h"

#include <type_traits>

using namespace std::string_view_literals;

class PrintForward : public Print
{
public:
    constexpr SuccessStatus operator()(ContainerVariant<std::vector, int, float> variant) const override
    {
        if not consteval
        {
            operator_impl(variant);
        }
        return true;
    }

    constexpr SuccessStatus operator()(ContainerVariant<std::list, int, float> variant) const override
    {
        if not consteval
        {
            operator_impl(variant);
        }
        return true;
    }

    constexpr std::string_view name() const override
    {
        using namespace std::string_view_literals;
        return "PrintForward"sv;
    }

    template<std::ranges::range Container>
    void operator()(std::reference_wrapper<Container> container);

private:
    void operator_impl(ContainerVariant<std::vector, int, float> variant) const;
    void operator_impl(ContainerVariant<std::list, int, float> variant) const;
};
