#pragma once

#include "../observer.h"
#include "../subjects/subject_print.h"
#include "../subjects/subject_value.h"

class ObserverSum : public Observer,
                    public Observer::Update<SubjectValue>,
                    public Observer::Update<SubjectPrint>
{
public:
    ~ObserverSum() override;

    void update(SubjectValue& subject) override;
    void update(SubjectPrint& subject) override;

    std::string_view name() const override;

private:
    int m_sum{};
};
