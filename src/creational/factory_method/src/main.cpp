#include "class.h"
#include "factory.h"

#include <memory>
#include <print>
#include <vector>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

void                     add_from_json(auto& objectStorage, const Json& json);
void                     build_objects(auto& objectStorage, const Factory& factory, const Json& objectArrayJson);
std::unique_ptr<Factory> construct_factory(const Json& json);

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

    add_from_json(objects, json1);
    add_from_json(objects, json2);
    add_from_json(objects, json3);
    add_from_json(objects, json4);

    for (const auto& el : objects)
        el->print();

    return 0;
}

void add_from_json(auto& objectStorage, const Json& json)
{
    std::unique_ptr<Factory> factory = construct_factory(json);

    auto objectArrayJson = json["objects"];
    build_objects(objectStorage, *factory, objectArrayJson);
}


void build_objects(auto& objectStorage, const Factory& factory, const Json& objectArrayJson)
{
    for (auto& objectJson : objectArrayJson)
    {
        auto object = factory.build(objectJson);
        objectStorage.push_back(std::move(object));
    }
}

std::unique_ptr<Factory> construct_factory(const Json& json)
{
    std::unique_ptr<Factory> factory;

    auto factoryType = json["factory"].get<int>();
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
