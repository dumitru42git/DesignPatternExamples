#include "class.h"
#include "factory.h"

#include <memory>
#include <print>
#include <vector>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

std::unique_ptr<Factory> pick_factory(int factoryType);
void build_objects(auto& factory, std::vector<std::unique_ptr<Class>>& objectStorage, auto& objectArrayJson);
void routine(std::vector<std::unique_ptr<Class>>& objectStorage, Json& json);

int main()
{
    std::println("---Factory Method---");

    // clang-format off
    Json json1{{"factory", 1},{"objects", {{}}}};
    Json json2{{"factory", 2},{"objects", {{}}}};
    Json json3{
        {"factory", 3},
        {"objects", {
            {{"type", "A"}, {"x", 1}, {"y", 2}},
            {{"type", "B"}, {"x", 3}},
            {{"type", "B"}, {"y", 4.1f}}
         }}
    };
    Json json4 = json3;
    json4["factory"] = 4;
    // clang-format on

    std::vector<std::unique_ptr<Class>> objects;

    routine(objects, json1);
    routine(objects, json2);
    routine(objects, json3);
    routine(objects, json4);

    for (auto& el : objects)
        el->print();

    return 0;
}

void routine(std::vector<std::unique_ptr<Class>>& objectStorage, Json& json)
{
    auto                     factoryType = json["factory"].get<int>();
    std::unique_ptr<Factory> factory     = pick_factory(factoryType);

    auto objectArrayJson = json["objects"];
    build_objects(factory, objectStorage, objectArrayJson);
}


void build_objects(auto& factory, std::vector<std::unique_ptr<Class>>& objectStorage, auto& objectArrayJson)
{
    for (auto& objectJson : objectArrayJson)
    {
        auto object = factory->build(objectJson);
        objectStorage.push_back(std::move(object));
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
        case 4:
            factory = std::make_unique<Factory4>();
            break;
    }
    return factory;
}
