#include "subject_print.h"
//
#include "../observer.h"
//
#include "../subject.inl"

#include <ostream>
#include <print>

using namespace std::string_view_literals;

SubjectPrint::SubjectPrint(std::ostream& stream)
        : m_stream{stream}
{
}

SubjectPrint::~SubjectPrint()
{
    std::print("{0}::~{0}() -> ", name());
}

void SubjectPrint::notify()
{
    std::println("SubjectPrint::notify()");
    Subject::notify(*this);
    std::println();
}

std::string_view SubjectPrint::name() const
{
    return "SubjectPrint"sv;
}

void SubjectPrint::print(std::string_view sv) const
{
    std::println(m_stream, "    {}", sv);
}
