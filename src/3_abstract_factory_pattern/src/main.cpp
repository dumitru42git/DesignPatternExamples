#include "classA.h"
#include "classB.h"
#include "factory.h"

#include <memory>
#include <print>
#include <vector>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

std::unique_ptr<Factory> pick_factory(int factoryType);
void                     build_call_objects(auto& factory, auto& objectArrayJson);
void                     routine(Json& json);

int main()
{
    std::println("---Abstract Factory Pattern---");

    // clang-format off
    Json json1{
        {"factory", 1},
        {"objects", {
            {{"type", "A"}, {"x", 1}, {"y", 2.1}},
            {{"type", "B"}, {"x", 3}},
            {{"type", "B"}, {"y", 4.1f}}
         }}
    };

    Json json2 = json1;
    json2["factory"] = 2;

    Json json3 = json1;
    json3["factory"] = 3;
    // clang-format on

    routine(json1);
    routine(json2);
    routine(json3);

    return 0;
}

void routine(Json& json)
{
    auto                     factoryType = json["factory"].get<int>();
    std::unique_ptr<Factory> factory     = pick_factory(factoryType);

    auto objectArrayJson = json["objects"];
    build_call_objects(factory, objectArrayJson);
}


void build_call_objects(auto& factory, auto& objectArrayJson)
{
    for (auto& objectJson : objectArrayJson)
    {
        if (objectJson["type"] == "A")
        {
            auto object = factory->buildA(objectJson);
            object->print();
        }
        else if (objectJson["type"] == "B")
        {
            auto object = factory->buildB(objectJson);
            object->print();
        }
    }
}

std::unique_ptr<Factory> pick_factory(int factoryType)
{
    std::unique_ptr<Factory> factory;
    switch (factoryType)
    {
        case 1:
            factory = std::make_unique<Factory1>();
            break;
        case 2:
            factory = std::make_unique<Factory2>();
            break;
        case 3:
            factory = std::make_unique<Factory3>();
            break;
    }
    return factory;
}
