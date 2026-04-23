#pragma once

#include "data.h"

#include <print>

class Command
{
public:
    virtual void execute() = 0;
    virtual void revert()  = 0;

    virtual ~Command() = default;
};

class SetCommand : public Command
{
public:
    SetCommand(Data& data, Data newData)
            : m_data{data}
            , m_oldData{data}
            , m_newData{newData}
    {
    }

    void execute() override
    {
        std::println("SetCommand::execute(): data = {}, newData = {}", m_data, m_newData);
        m_oldData = m_data;
        m_data    = m_newData;
        std::println(" -> data = {}", m_data);
    }

    void revert() override
    {
        std::println("SetCommand::revert(): data = {}, oldData = {}", m_data, m_oldData);
        m_data = m_oldData;
        std::println(" -> data = {}", m_data);
    }

private:
    Data& m_data;
    Data  m_oldData;
    Data  m_newData;
};

class AddCommand : public Command
{
public:
    AddCommand(Data& data, int value)
            : m_data{data}
            , m_value{value}
    {
    }

    void execute() override
    {
        std::println("AddCommand::execute(): data = {}, value = {}", m_data, m_value);
        m_data.value += m_value;
        std::println(" -> data = {}", m_data);
    }

    void revert() override
    {
        std::println("AddCommand::revert(): data = {}, value = {}", m_data, m_value);
        m_data.value -= m_value;
        std::println(" -> data = {}", m_data);
    }

private:
    Data& m_data;
    int   m_value;
};
