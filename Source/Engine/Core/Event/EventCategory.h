#pragma once

#include <Core/Primitives.h>

namespace GGE
{
    enum class EventCategory : uint32
    {
        None = 0,
        Input = BIT(0),
        Window = BIT(1),
        Application = BIT(2),
        Engine = BIT(3),
        Physics = BIT(4),
        Graphics = BIT(5),
        Audio = BIT(6),
        Network = BIT(7)
    };

    inline EventCategory operator|(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(
            static_cast<uint32>(lhs) | static_cast<uint32>(rhs));
    }

    inline EventCategory operator&(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(
            static_cast<uint32>(lhs) & static_cast<uint32>(rhs));
    }

    inline EventCategory operator^(EventCategory lhs, EventCategory rhs)
    {
        return static_cast<EventCategory>(
            static_cast<uint32>(lhs) ^ static_cast<uint32>(rhs));
    }

    inline EventCategory& operator|=(EventCategory& lhs, EventCategory rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }
}
