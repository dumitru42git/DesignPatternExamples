#include "subject_string.h"
//
#include "../observer.h"
//
#include "../subject.inl"

#include <algorithm>
#include <print>

using namespace std::string_view_literals;

SubjectString::SubjectString(std::string string)
        : m_string{std::move(string)}
{
}

SubjectString::~SubjectString()
{
    std::print("{0}::~{0}() -> ", name());
}

void SubjectString::notify()
{
    std::println("SubjectString::notify(), m_string = \"{}\"", m_string);
    Subject::notify(*this);
    updateString();
    std::println();
}

std::string_view SubjectString::name() const
{
    return "SubjectString"sv;
}

std::string_view SubjectString::string() const
{
    return m_string;
}

void SubjectString ::updateString()
{
    if (m_string.empty())
    {
        m_string.append("A");
        return;
    }

    const auto last    = m_string.back();
    auto       newLast = std::clamp(last, 'A', 'z');
    newLast++;

    if (newLast > 'z')
        newLast = 'A';

    m_string.back() = newLast;
}
