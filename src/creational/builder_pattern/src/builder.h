#pragma once
#include "class.h"

#include <memory>

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Builder
{
public:
    virtual void buildX(const Json& json) {};
    virtual void buildY(const Json& json) {};

    virtual std::unique_ptr<Class> getResult() const = 0;

    virtual ~Builder() = default;
};

class BuilderA : public Builder
{
public:
    void                   buildX(const Json& json) override;
    void                   buildY(const Json& json) override;
    std::unique_ptr<Class> getResult() const override;

private:
    int m_x{}, m_y{};
};

class BuilderB : public Builder
{
public:
    void                   buildX(const Json& json) override;
    std::unique_ptr<Class> getResult() const override;

private:
    double m_x{};
};
