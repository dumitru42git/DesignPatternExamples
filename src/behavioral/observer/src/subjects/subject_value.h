#pragma once
#include "../subject.h"

class SubjectValue : public Subject
{
public:
    SubjectValue(int value);
    ~SubjectValue() override;

    void             notify() override;
    std::string_view name() const override;

    int value() const;

private:
    int m_value;
};
