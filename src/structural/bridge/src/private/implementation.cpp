#pragma once

#include "implementation.h"

#include <print>

Implementation::~Implementation() = default;

void ImplementationA::print(std::string_view callerName) const
{
    std::println("{} -> ImplementationA: m_data = {}", callerName, m_data);
}

void ImplementationA::setData(int data)
{
    m_data = data;
}

void ImplementationB::print(std::string_view callerName) const
{
    std::println("{} -> ImplementationB: m_x = {}, m_y = {}", callerName, m_x, m_y);
}

void ImplementationB::setData(int data)
{
    m_x = data;
    m_y = data;
}
