#pragma once

#include <format>

struct Request
{
    int data;
    enum Type
    {
        PRINT,
        RESET
    } type;

    static constexpr std::string_view typeToString(Type type)
    {
        std::string_view str;
        switch (type)
        {
            case PRINT:
                str = "PRINT";
                break;
            case RESET:
                str = "RESET";
                break;
            default:
                str = "unknown type";
                break;
        }
        return str;
    }
};

template<>
struct std::formatter<Request>
{
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto format(const Request& request, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{{data = {}, type = {}}}", request.data, Request::typeToString(request.type));
    }
};
