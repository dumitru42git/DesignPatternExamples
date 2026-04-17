#include "factory.h"

// Factory1

std::unique_ptr<ClassA> Factory1::buildA(const Json& json) const
{
    return std::make_unique<ClassA1>(json["x"].get<int>(), json["y"].get<int>());
}

std::unique_ptr<ClassB> Factory1::buildB(const Json& json) const
{
    std::unique_ptr<ClassB> object;
    if (json.contains("x"))
    {
        object = std::make_unique<ClassB1>(json["x"].get<int>());
    }
    else if (json.contains("y"))
    {
        object = std::make_unique<ClassB1>(json["y"].get<float>());
    }
    return object;
}

// Factory2

std::unique_ptr<ClassA> Factory2::buildA(const Json& json) const
{
    return std::make_unique<ClassA2>(json["x"].get<double>(), json["y"].get<double>());
}

std::unique_ptr<ClassB> Factory2::buildB(const Json& json) const
{
    double value = 0.0;
    if (json.contains("x"))
    {
        value = json["x"].get<double>();
    }
    else if (json.contains("y"))
    {
        value = json["y"].get<double>();
    }
    return std::make_unique<ClassB2>(value);
}

// Factory3

std::unique_ptr<ClassA> Factory3::buildA(const Json& json) const
{
    return std::make_unique<ClassA1>(json["x"].get<int>(), json["y"].get<int>());
}

std::unique_ptr<ClassB> Factory3::buildB(const Json& json) const
{
    double value = 0.0;
    if (json.contains("x"))
    {
        value = json["x"].get<double>();
    }
    else if (json.contains("y"))
    {
        value = json["y"].get<double>();
    }
    return std::make_unique<ClassB2>(value);
}
