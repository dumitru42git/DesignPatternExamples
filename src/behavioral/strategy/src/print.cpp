#include "print.h"

#include <print>

void Print::print_default(const std::type_info& info) const
{
    std::println("{}: default implementation ({})", this->name(), info.name());
}

void Print::print_unsupported(const std::type_info& info) const
{
    std::println("{}: unsupported argument ({})", this->name(), info.name());
}
