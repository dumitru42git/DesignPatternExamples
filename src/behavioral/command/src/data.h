#pragma once

#include <format>

struct Data
{
    int value{};
};

template<>
class std::formatter<Data>
{
public:
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto format(const Data& data, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}", data.value);
    }
};
