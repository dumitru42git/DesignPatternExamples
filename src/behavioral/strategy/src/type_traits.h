#pragma once

#include <type_traits>

template<template<typename...> typename T, template<typename...> typename U>
struct is_same_template : std::false_type
{
};

template<template<typename...> typename T>
struct is_same_template<T, T> : std::true_type
{
};

template<template<typename...> typename T, template<typename...> typename U>
concept same_template_as = is_same_template<T, U>::value;
