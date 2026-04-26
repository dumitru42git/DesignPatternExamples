#pragma once
#include "../subject.h"

#include <string>
#include <string_view>

class SubjectString : public Subject
{
public:
    SubjectString(std::string string);
    ~SubjectString() override;

    void             notify() override;
    std::string_view name() const override;

    std::string_view string() const;

private:
    void updateString();

private:
    std::string m_string;
};
