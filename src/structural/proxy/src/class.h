#pragma once

#include <string_view>

#include <expected>

using namespace std::string_view_literals;

enum class ReturnError
{
    UNAUTHORIZED,
    SUSPENDED,
    UNAVAILABLE
};

class Class
{
public:
    virtual std::expected<int, ReturnError> getData(int clientData) = 0;
    virtual std::string_view                className() const       = 0;

    virtual ~Class() = default;
};

class ClassUnsecure : public Class
{
public:
    ClassUnsecure(int data)
            : m_data{data}
    {
    }

    std::expected<int, ReturnError> getData(int clientData) override //
    {
        return m_data;
    }

    std::string_view className() const override { return "ClassUnsecure"sv; };

private:
    int m_data;
};

constexpr std::string_view ReturnErrorToStringView(const ReturnError err)
{
    std::string_view result;
    switch (err)
    {
        case ReturnError::SUSPENDED:
            result = "SUSPENDED"sv;
            break;
        case ReturnError::UNAUTHORIZED:
            result = "UNAUTHORIZED"sv;
            break;
        case ReturnError::UNAVAILABLE:
            result = "UNAVAILABLE"sv;
            break;
        default:
            result = "unknown error"sv;
    }
    return result;
}
