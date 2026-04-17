#include "factory.h"

std::unique_ptr<Class> Factory1::build(const Json& json) const
{
    return std::make_unique<ClassA>(0, 0);
}

std::unique_ptr<Class> Factory2::build(const Json& json) const
{
    return std::make_unique<ClassB>(0.0f);
}

std::unique_ptr<Class> Factory3::build(const Json& json) const
{
    std::unique_ptr<Class> object;

    auto type = json["type"].get<std::string_view>();
    if (type == "A")
    {
        object = std::make_unique<ClassA>(json["x"].get<int>(), json["y"].get<int>());
    }
    else if (type == "B")
    {
        if (json.contains("x"))
        {
            object = std::make_unique<ClassB>(json["x"].get<int>());
        }
        else if (json.contains("y"))
        {
            object = std::make_unique<ClassB>(json["y"].get<float>());
        }
    }

    return object;
}

std::unique_ptr<Class> Factory4::build(const Json& json) const
{
    std::unique_ptr<Class> object;

    auto type = json["type"].get<std::string_view>();
    if (type == "A") // ClassB
    {
        object = std::make_unique<ClassB>(json["x"].get<int>() + json["y"].get<int>());
    }
    else if (type == "B") // ClassA
    {
        if (json.contains("x"))
        {
            object = std::make_unique<ClassA>(json["x"].get<int>(), 0);
        }
        else if (json.contains("y"))
        {
            object = std::make_unique<ClassA>(0, json["y"].get<int>());
        }
    }

    return object;
}
