#pragma once

#include "type_traits.h"

#include <list>
#include <string_view>
#include <type_traits>
#include <typeinfo>
#include <variant>
#include <vector>

class Print
{
public:
    template<template<typename> typename Container, typename... Ts>
    using ContainerVariant = std::variant<std::reference_wrapper<const Container<Ts>>...>;

    using SuccessStatus = bool;

public:
    virtual constexpr ~Print() = default;

    virtual constexpr SuccessStatus operator()(ContainerVariant<std::vector, int, float> variant) const
    {
        return default_operator(variant);
    }

    virtual constexpr SuccessStatus operator()(ContainerVariant<std::list, int, float> variant) const
    {
        return default_operator(variant);
    }

    template<template<typename> typename Container, typename... Ts>
        requires(!same_template_as<Container, std::reference_wrapper>)
    constexpr SuccessStatus operator()(const Container<Ts...>& container) const
    {
        if constexpr (requires { (*this)(std::cref(container)); })
            return (*this)(std::cref(container));
        else
        {
            if (!std::is_constant_evaluated())
                print_unsupported(typeid(container));
            return false;
        }
    }

    virtual constexpr std::string_view name() const = 0;

private:
    constexpr SuccessStatus default_operator(auto variant) const
    {
        if (!std::is_constant_evaluated())
            std::visit([this](const auto& container) { print_default(typeid(container.get())); }, variant);
        return false;
    }

    void print_unsupported(const std::type_info& info) const;
    void print_default(const std::type_info& info) const;
};
