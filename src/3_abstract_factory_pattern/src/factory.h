#pragma once
#include "classA.h"
#include "classB.h"

#include <memory>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Factory
{
public:
    virtual std::unique_ptr<ClassA> buildA(Json& json) = 0;
    virtual std::unique_ptr<ClassB> buildB(Json& json) = 0;
    virtual ~Factory()                                 = default;
};

class Factory1 : public Factory
{
public:
    std::unique_ptr<ClassA> buildA(Json& json) override;
    std::unique_ptr<ClassB> buildB(Json& json) override;
};

class Factory2 : public Factory
{
public:
    std::unique_ptr<ClassA> buildA(Json& json) override;
    std::unique_ptr<ClassB> buildB(Json& json) override;
};

class Factory3 : public Factory
{
public:
    std::unique_ptr<ClassA> buildA(Json& json) override;
    std::unique_ptr<ClassB> buildB(Json& json) override;
};
