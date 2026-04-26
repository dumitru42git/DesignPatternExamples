#include "observer_sum.h"
//
#include "../subjects/subject_print.h"
#include "../subjects/subject_value.h"

#include <format>
#include <print>

using namespace std::string_view_literals;

ObserverSum::~ObserverSum()
{
    std::print("{0}::~{0}() -> ", name());
}

void ObserverSum::update(SubjectValue& subject)
{
    const auto oldSum = m_sum;
    const auto value  = subject.value();
    const auto newSum = oldSum + value;
    m_sum             = newSum;
    std::println("    {}::update({}): oldSum = {}, newSum = {}", name(), subject.name(), oldSum, m_sum);
}

void ObserverSum::update(SubjectPrint& subject)
{
    subject.print(std::format("ObserverSum::m_sum = {}", m_sum));
}

std::string_view ObserverSum::name() const
{
    return "ObserverSum"sv;
}
