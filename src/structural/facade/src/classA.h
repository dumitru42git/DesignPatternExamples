#pragma once

#include <optional>
#include <print>

class ClassA
{
public:
    std::optional<int> run(int seed)
    {
        std::optional<int> result;
        if (seed % 2 == 0)
        {
            result = seed;
            std::println("ClassA::run({}) -> {}", seed, result.value());
        }
        else
        {
            std::println("ClassA::run({}) -> std::nullopt", seed);
        }

        return result;
    }
};
