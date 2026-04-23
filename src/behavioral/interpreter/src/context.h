#pragma once

#include "node.h"
#include "nodes/value.h"

#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

class Context
{
public:
    void                 set(std::string varName, Value value);
    std::optional<Value> get(std::string_view varName);

private:
    struct string_hash
    {
        using hash_type      = std::hash<std::string_view>;
        using is_transparent = void;

        std::size_t operator()(const char* str) const { return hash_type{}(str); }
        std::size_t operator()(std::string_view str) const { return hash_type{}(str); }
        std::size_t operator()(std::string const& str) const { return hash_type{}(str); }
    };

    std::unordered_map<std::string, Value, string_hash, std::equal_to<>> m_map;
};
