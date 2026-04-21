#pragma once

class ClassC
{
public:
    int run(int value)
    {
        int result = value / 2;
        std::println("ClassC::run({}) -> {}", value, result);
        return result;
    }
};
