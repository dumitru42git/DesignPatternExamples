#include "builder.h"
#include "class.h"

#include <memory>
#include <print>
#include <vector>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

std::vector<std::unique_ptr<Class>> objects_from_json(const Json& classArrayJson);
void                                build_objects(auto& objectStorage, const Builder& builder, int count);
std::unique_ptr<Builder>            construct_builder(const Json& classJson);
void                                print_objects(const auto& objects);

int main()
{
    std::println("---Builder Pattern---");

    // clang-format off
    Json json{
        {{"class", "A"},
         {"data", {{"x", 1}, {"y", 2.1}}},
         {"count", 3}
        },
        {{"class", "B"},
         {"data", {{"x1", 3}, {"x2", 0.54}}},
         {"count", 2}
        },
    };
    // clang-format on

    auto objects = objects_from_json(json);
    print_objects(objects);

    return 0;
}

std::vector<std::unique_ptr<Class>> objects_from_json(const Json& classArrayJson)
{
    std::vector<std::unique_ptr<Class>> objects;
    for (auto& classJson : classArrayJson)
    {
        std::unique_ptr<Builder> builder = construct_builder(classJson);

        int count = classJson["count"].get<int>();
        build_objects(objects, *builder, count);
    }
    return objects;
}

void build_objects(auto& objectStorage, const Builder& builder, const int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::unique_ptr<Class> obj = builder.getResult();
        objectStorage.push_back(std::move(obj));
    }
}

std::unique_ptr<Builder> construct_builder(const Json& classJson)
{
    std::unique_ptr<Builder> builder;
    auto                     classType = classJson["class"].get<std::string_view>();

    if (classType == "A")
    {
        builder = std::make_unique<BuilderA>();
    }
    else if (classType == "B")
    {
        builder = std::make_unique<BuilderB>();
    }

    builder->buildX(classJson["data"]);
    builder->buildY(classJson["data"]);

    return builder;
}

void print_objects(const auto& objects)
{
    for (auto& object : objects)
    {
        object->print();
    }
}
