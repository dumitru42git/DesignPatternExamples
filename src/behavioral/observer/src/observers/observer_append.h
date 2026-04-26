#pragma once

#include "../observer.h"
#include "../subjects/subject_print.h"
#include "../subjects/subject_string.h"
#include "../subjects/subject_value.h"

#include <string>

class ObserverAppend : public Observer,
                       public Observer::Update<SubjectString>,
                       public Observer::Update<SubjectValue>,
                       public Observer::Update<SubjectPrint>
{
public:
    ~ObserverAppend() override;

    void update(SubjectString& subject) override;
    void update(SubjectPrint& subject) override;

    std::string_view name() const override;

private:
    std::string m_string{};
};
