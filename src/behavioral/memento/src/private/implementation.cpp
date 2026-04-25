#pragma once

#include "implementation.h"

#include <print>

// Implementation

std::unique_ptr<Implementation> Implementation::clone() const
{
    return std::unique_ptr<Implementation>(cloneImpl());
}


// ImplementationA

void ImplementationA::print(std::string_view callerName) const
{
    std::println("{} -> ImplementationA: m_data = {}", callerName, m_data);
}

void ImplementationA::setData(int data)
{
    m_data = data;
}

std::unique_ptr<ImplementationA> ImplementationA::clone() const
{
    return std::unique_ptr<ImplementationA>(cloneImpl());
}

ImplementationA* ImplementationA::cloneImpl() const
{
    return new auto(*this);
}


// ImplementationB

void ImplementationB::print(std::string_view callerName) const
{
    std::println("{} -> ImplementationB: m_x = {}, m_y = {}", callerName, m_x, m_y);
}

void ImplementationB::setData(int data)
{
    m_x = data;
    m_y = data;
}

std::unique_ptr<ImplementationB> ImplementationB::clone() const
{
    return std::unique_ptr<ImplementationB>(cloneImpl());
}

ImplementationB* ImplementationB::cloneImpl() const
{
    return new auto(*this);
}
