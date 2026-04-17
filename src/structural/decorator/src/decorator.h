#pragma once

#include "class.h"

#include <memory>

class Decorator : public Class
{
public:
    Decorator(std::unique_ptr<Class> object)
            : m_object{std::move(object)}
    {
    }

    [[nodiscard]] std::string printString() const override //
    {
        std::string result;
        if (hasObject())
            result = m_object->printString();
        return result;
    }

    int getId() const override
    {
        int id = 0;
        if (hasObject())
            id = m_object->getId();
        return id;
    }

protected:
    bool hasObject() const { return m_object.operator bool(); }

private:
    std::unique_ptr<Class> m_object;
};

class DecoratorAddIdPre : public Decorator
{
public:
    DecoratorAddIdPre(std::unique_ptr<Class> object)
            : Decorator(std::move(object))
    {
    }

    [[nodiscard]] std::string printString() const override //
    {
        std::string result;

        if (hasObject())
            result = std::format("m_id = {}, {}", Decorator::getId(), Decorator::printString());

        return result;
    }
};

class DecoratorAddIdPost : public Decorator
{
public:
    DecoratorAddIdPost(std::unique_ptr<Class> object)
            : Decorator(std::move(object))
    {
    }

    [[nodiscard]] std::string printString() const override //
    {
        std::string result;

        if (hasObject())
            result = std::format("{}, m_id = {}", Decorator::printString(), Decorator::getId());

        return result;
    }
};

class DecoratorInvalidId : public Decorator
{
public:
    DecoratorInvalidId(std::unique_ptr<Class> object)
            : Decorator(std::move(object))
    {
    }

    int getId() const override //
    {
        return -1;
    }
};
