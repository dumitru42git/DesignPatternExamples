#pragma once

#include <cmath>
#include <print>

class ClassB
{
public:
    int run(int value)
    {
        int result = value + 2 * std::abs(value);
        std::println("ClassB::run({}) -> {}", value, result);
        return result;
    }
};
