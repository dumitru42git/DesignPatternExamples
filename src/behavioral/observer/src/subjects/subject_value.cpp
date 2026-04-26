#include "subject_value.h"
//
#include "../observer.h"
//
#include "../subject.inl"

#include <print>

using namespace std::string_view_literals;

SubjectValue::SubjectValue(int value)
        : m_value{value}
{
}

SubjectValue::~SubjectValue()
{
    std::print("{0}::~{0}() -> ", name());
}

void SubjectValue::notify()
{
    std::println("SubjectValue::notify(), m_value = {}", m_value);
    Subject::notify(*this);
    std::println();
}

std::string_view SubjectValue::name() const
{
    return "SubjectValue"sv;
}

int SubjectValue::value() const
{
    return m_value;
}
