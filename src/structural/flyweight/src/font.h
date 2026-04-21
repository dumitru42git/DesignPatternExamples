#pragma once

#include <string>
#include <string_view>

class Font
{
public:
    Font(std::string description)
            : m_description{std::move(description)}
    {
    }

    std::string_view description() const { return m_description; }

private:
    std::string m_description;
};
