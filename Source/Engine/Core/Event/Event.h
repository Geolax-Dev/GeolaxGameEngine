#pragma once

#include <Core/Event/EventCategory.h>

#define EVENT_TYPE(type) \
    static constexpr GGE::EventType GetStaticType() { return type; } \
    virtual GGE::EventType GetEventType() const override { return type; } \
    virtual const char* GetName() const override { return #type; }

namespace GGE
{
    typedef uint32 EventType;

    class Event
    {
        public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual EventCategory GetCategoryFlags() const = 0;
        inline bool IsInCategory(EventCategory category) const
        {
            return static_cast<int>(GetCategoryFlags() & category) != 0;
        }
    };

    // Input events are events that are related to user input, such as keyboard and mouse events.
    class InputEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Input;
        }
    };

    // Window events are events that are related to the window, such as window resize and close events.
    class WindowEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Window;
        }
    };

    // Application events are events that are related to the application, such as application start and stop events.
    class ApplicationEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Application;
        }
    };

    // Engine events are events that are related to the engine, such as engine start and stop events.
    class EngineEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Engine;
        }
    };

    // Physics events are events that are related to the physics engine, such as collision events.
    class PhysicsEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Physics;
        }
    };

    // Graphics events are events that are related to the graphics engine, such as rendering events.
    class GraphicsEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Graphics;
        }
    };

    // Audio events are events that are related to the audio engine, such as sound playback events.
    class AudioEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Audio;
        }
    };

    // Network events are events that are related to the network, such as connection and disconnection events.
    class NetworkEvent : public Event
    {
        public:
        virtual EventCategory GetCategoryFlags() const override
        {
            return EventCategory::Network;
        }
    };
}
