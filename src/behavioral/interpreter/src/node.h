#pragma once

#include <memory>
#include <print>
#include <string>

class Context;
enum class EvaluateResultCode;

class Node
{
public:
    virtual std::unique_ptr<Node> evaluate(Context& ctx)                           = 0;
    virtual std::unique_ptr<Node> evaluate(Context& ctx, EvaluateResultCode& code) = 0;
    virtual void                  printInfo() const                                = 0;
    virtual std::string           string() const                                   = 0;
    virtual ~Node()                                                                = default;

public:
    void print() const { std::println("{}", this->string()); }
};

enum class EvaluateResultCode
{
    EVALUATED,
    UNEVALUATED
};

template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
