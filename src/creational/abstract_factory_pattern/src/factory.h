#pragma once
#include "classA.h"
#include "classB.h"

#include <memory>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Factory
{
public:
    virtual std::unique_ptr<ClassA> buildA(const Json& json) const = 0;
    virtual std::unique_ptr<ClassB> buildB(const Json& json) const = 0;
    virtual ~Factory()                                             = default;
};

class Factory1 : public Factory
{
public:
    std::unique_ptr<ClassA> buildA(const Json& json) const override;
    std::unique_ptr<ClassB> buildB(const Json& json) const override;
};

class Factory2 : public Factory
{
public:
    std::unique_ptr<ClassA> buildA(const Json& json) const override;
    std::unique_ptr<ClassB> buildB(const Json& json) const override;
};

class Factory3 : public Factory
{
public:
    std::unique_ptr<ClassA> buildA(const Json& json) const override;
    std::unique_ptr<ClassB> buildB(const Json& json) const override;
};
