#include "context.h"
#include "nodes/value.h"

#include <print>

void Context::set(std::string varName, Value value) //
{
    std::println("\"{}\" = {}", varName, value.string());
    m_map[std::move(varName)] = value;
}

std::optional<Value> Context::get(std::string_view varName)
{
    std::optional<Value> value;

    auto it = m_map.find(varName);
    if (it != m_map.end())
        value = it->second;

    return value;
}
