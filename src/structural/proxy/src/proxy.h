#pragma once

#include "class.h"

#include <functional>
#include <memory>
#include <string_view>

using namespace std::string_view_literals;

class ProxySecure : public Class
{
public:
    ProxySecure(Class& object, std::function<bool(int)> clientDataCheck, const int maxFailCount = 3)
            : m_object{&object}
            , m_clientDataCheck{std::move(clientDataCheck)}
            , m_maxFailCount{maxFailCount}
    {
    }

    std::expected<int, ReturnError> getData(const int clientData) override //
    {
        std::expected<int, ReturnError> result;
        if (!m_object)
        {
            result = std::unexpected{ReturnError::UNAVAILABLE};
        }
        else if (m_clientDataCheck(clientData))
        {
            result = m_object->getData(clientData);
        }
        else
        {
            m_currentFailCount++;
            if (m_currentFailCount == m_maxFailCount)
            {
                m_object = nullptr;
                result   = std::unexpected{ReturnError::SUSPENDED};
            }
            else
            {
                result = std::unexpected{ReturnError::UNAUTHORIZED};
            }
        }

        return result;
    }

    std::string_view className() const override { return "ProxySecure"sv; };

private:
    Class*                   m_object;
    std::function<bool(int)> m_clientDataCheck;
    const int                m_maxFailCount     = 0;
    int                      m_currentFailCount = 0;
};
