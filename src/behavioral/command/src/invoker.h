#pragma once

#include "command.h"

#include <memory>
#include <queue>
#include <stack>

class Invoker
{
public:
    void addCommand(std::unique_ptr<Command> command) //
    {
        m_pending.push(std::move(command));
    }

    void execute()
    {
        if (m_pending.empty())
        {
            std::println("Invoker::execute(): pending queue empty");
            return;
        }

        auto command = std::move(m_pending.front());
        m_pending.pop();

        command->execute();
        m_done.push(std::move(command));

        m_undone = {};
    }

    void undo()
    {
        if (m_done.empty())
        {
            std::println("Invoker::undo(): done stack empty");
            return;
        }

        auto command = std::move(m_done.top());
        m_done.pop();

        command->revert();
        m_undone.push(std::move(command));
    }

    void redo()
    {
        if (m_undone.empty())
        {
            std::println("Invoker::redo(): undone stack empty");
            return;
        }

        auto command = std::move(m_undone.top());
        m_undone.pop();

        command->execute();
        m_done.push(std::move(command));
    }

private:
    std::queue<std::unique_ptr<Command>> m_pending;
    std::stack<std::unique_ptr<Command>> m_done;
    std::stack<std::unique_ptr<Command>> m_undone;
};
