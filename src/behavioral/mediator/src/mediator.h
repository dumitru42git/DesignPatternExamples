#pragma once
#include "class.h"

#include <array>
#include <unordered_map>

class Mediator
{
public:
    void sendMessage(const Class& sender, const Class::ID& receiverId)
    {
        const std::array listenersArray = {&m_listeners.allowUnicast, &m_listeners.allowAll};
        const auto&      message        = sender.message();

        for (auto* const listeners : listenersArray)
        {
            const auto it = listeners->find(receiverId);
            if (it != listeners->end())
            {
                const auto& receiver = it->second;
                receiver->process(message);
            }
        }
    }

    auto sendMessage(const Class& sender, const std::same_as<Class::ID> auto&... receiverIds)
    {
        const std::array listenersArray  = {&m_listeners.allowMulticast, &m_listeners.allowAll};
        const std::array receiverIdArray = {receiverIds...};
        const auto&      message         = sender.message();

        for (auto* const listeners : listenersArray)
        {
            for (const auto& receiverId : receiverIdArray)
            {
                const auto it = listeners->find(receiverId);
                if (it != listeners->end())
                {
                    const auto& receiver = it->second;
                    receiver->process(message);
                }
            }
        }
    }

    void sendMessage(const Class& sender)
    {
        const std::array listenersArray = {&m_listeners.allowBroadcast, &m_listeners.allowAll};
        const auto&      message        = sender.message();

        for (auto* const listeners : listenersArray)
        {
            for (auto listener : *listeners)
            {
                const auto& receiver = listener.second;
                receiver->process(message);
            }
        }
    }

    void addListener(Class& object)
    {
        const auto allowedCastType = object.allowedReceiveCastType();
        const auto id              = object.id();

        if (allowedCastType == Class::CastType::ALL)
        {
            m_listeners.allowAll[id] = &object;
        }
        else
        {
            if (allowedCastType & Class::CastType::UNICAST)
            {
                m_listeners.allowUnicast[id] = &object;
            }
            if (allowedCastType & Class::CastType::MULTICAST)
            {
                m_listeners.allowMulticast[id] = &object;
            }
            if (allowedCastType & Class::CastType::BROADCAST)
            {
                m_listeners.allowBroadcast[id] = &object;
            }
        }
    }

private:
    struct
    {
        std::unordered_map<Class::ID, Class*> allowUnicast;
        std::unordered_map<Class::ID, Class*> allowMulticast;
        std::unordered_map<Class::ID, Class*> allowBroadcast;
        std::unordered_map<Class::ID, Class*> allowAll;
    } m_listeners;
};
