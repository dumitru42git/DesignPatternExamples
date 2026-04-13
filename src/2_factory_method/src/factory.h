#pragma once
#include "class.h"

#include <memory>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Factory
{
public:
    virtual std::unique_ptr<Class> build(Json& json) = 0;
    virtual ~Factory()                              = default;
};

class Factory1 : public Factory
{
public:
    std::unique_ptr<Class> build(Json& json) override;
};

class Factory2 : public Factory
{
public:
    std::unique_ptr<Class> build(Json& json) override;
};

class Factory3 : public Factory
{
public:
    std::unique_ptr<Class> build(Json& json) override;
};

class Factory4 : public Factory
{
public:
    std::unique_ptr<Class> build(Json& json) override;
};
