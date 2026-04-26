#pragma once
#include "../subject.h"

#include <iosfwd>
#include <string_view>

class SubjectPrint : public Subject
{
public:
    SubjectPrint(std::ostream& stream);
    ~SubjectPrint() override;

    void             notify() override;
    std::string_view name() const override;

    void print(std::string_view sv) const;

private:
    std::ostream& m_stream;
};
