#include "observer_append.h"
//
#include "../subjects/subject_print.h"
#include "../subjects/subject_string.h"

#include <format>
#include <print>

using namespace std::string_view_literals;

ObserverAppend::~ObserverAppend()
{
    std::print("{0}::~{0}() -> ", name());
}

void ObserverAppend::update(SubjectString& subject)
{
    std::print("    {}::update({}): oldString = \"{}\"", name(), subject.name(), m_string);
    m_string.append(subject.string());
    std::println(", newString = \"{}\"", m_string);
}

void ObserverAppend::update(SubjectPrint& subject)
{
    subject.print(std::format("ObserverAppend::m_string = \"{}\"", m_string));
}

std::string_view ObserverAppend::name() const
{
    return "ObserverAppend"sv;
}
