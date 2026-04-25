#pragma once

#include <array>
#include <format>
#include <string>
#include <string_view>
#include <utility>

class Class
{
public:
    using ID = int;

    enum CastType
    {
        NONE      = 0,
        UNICAST   = 1,
        MULTICAST = 2,
        BROADCAST = 4,
        ALL       = UNICAST | MULTICAST | BROADCAST
    };

    friend constexpr auto operator&(CastType lhs, CastType rhs)
    {
        return static_cast<CastType>(std::to_underlying(lhs) & std::to_underlying(rhs));
    }

    friend constexpr auto operator|(CastType lhs, CastType rhs)
    {
        return static_cast<CastType>(std::to_underlying(lhs) | std::to_underlying(rhs));
    }

public:
    Class(CastType allowedIncomingCastType)
            : m_message{std::to_string(id_generator)}
            , m_processed{m_message}
            , m_ID{id_generator++}
            , m_allowedIncomingCastType{allowedIncomingCastType}
    {
    }

    std::string_view message() const { return m_message; }
    std::string_view processed() const { return m_processed; }
    void             process(std::string_view incomingMessage) { m_processed += std::format(", {}", incomingMessage); }

    ID       id() const { return m_ID; }
    CastType allowedReceiveCastType() const { return m_allowedIncomingCastType; }

private:
    inline static ID id_generator = 1;

private:
    std::string m_message;
    std::string m_processed;

    ID       m_ID;
    CastType m_allowedIncomingCastType;
};

template<>
struct std::formatter<Class::CastType> : std::formatter<std::string_view>
{
    auto format(const Class::CastType& castType, std::format_context& ctx) const
    {
        const auto index = static_cast<std::size_t>(castType);
        return std::formatter<std::string_view>::format(string_table[index], ctx);
    }

private:
    template<Class::CastType castType>
    static consteval std::string_view castTypeToString()
    {
        using CastType = Class::CastType;

        auto array_maker = []() {
            auto string_maker = []() constexpr -> std::string {
                std::string result;
                switch (castType)
                {
                    case CastType::NONE:
                        result = "NONE";
                        break;
                    case CastType::UNICAST:
                        result = "UNICAST";
                        break;
                    case CastType::MULTICAST:
                        result = "MULTICAST";
                        break;
                    case CastType::BROADCAST:
                        result = "BROADCAST";
                        break;
                    case CastType::ALL:
                        result = "ALL";
                        break;
                    default:
                        if ((castType & Class::CastType::UNICAST) != 0)
                        {
                            result += "U|";
                        }
                        if ((castType & Class::CastType::MULTICAST) != 0)
                        {
                            result += "M|";
                        }
                        if ((castType & Class::CastType::BROADCAST) != 0)
                        {
                            result += "B|";
                        }
                        result.pop_back();
                }
                return result;
            };

            constexpr std::size_t size   = string_maker().size();
            const auto            string = string_maker();

            std::array<char, size> array;
            std::copy(string.begin(), string.end(), array.begin());

            return array;
        };

        static constexpr auto array = array_maker();
        return std::string_view{array.begin(), array.end()};
    }

    template<auto... Is>
    static consteval auto makeCastTypeStringTable(std::index_sequence<Is...>)
    {
        return std::array{castTypeToString<static_cast<Class::CastType>(Is)>()...};
    }

    static constexpr std::array string_table =
        makeCastTypeStringTable(std::make_index_sequence<static_cast<std::size_t>(Class::CastType::ALL) + 1>());
};
