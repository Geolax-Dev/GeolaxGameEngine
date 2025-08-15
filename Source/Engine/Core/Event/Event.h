#pragma once

#include <Core/Event/EventCategory.h>
#include <functional>

#define EVENT_TYPE(type) \
    static constexpr GGE::EventType GetStaticType() { return type; } \
    virtual GGE::EventType GetEventType() const override { return type; } \
    virtual const char* GetName() const override { return #type; }

#define SIMPLE_EVENT_DEFINE(baseEventCategory, eventType) \
struct eventType ## Event : baseEventCategory \
{ \
    EVENT_TYPE( baseEventCategory ## s_ ## eventType )\
};

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

    using EventCallbackFn = std::function<void(Event&)>;
    using WindowEventCallbackFn = std::function<void(WindowEvent&)>;
    using InputEventCallbackFn = std::function<void(InputEvent&)>;
    using ApplicationEventCallbackFn = std::function<void(ApplicationEvent&)>;
    using EngineEventCallbackFn = std::function<void(EngineEvent&)>;
    using PhysicsEventCallbackFn = std::function<void(PhysicsEvent&)>;
    using GraphicsEventCallbackFn = std::function<void(GraphicsEvent&)>;
    using AudioEventCallbackFn = std::function<void(AudioEvent&)>;
    using NetworkEventCallbackFn = std::function<void(NetworkEvent&)>;

    template<class CallbackType>
    class EventSubscribers
    {
    public:
        EventSubscribers() = default;

        template<class...Args>
        void NotifyAll(Args&&... args)
        {
            for (auto& callback : m_callbacks)
                callback(std::forward<Args>(args)...);
        }

        void operator+=(const CallbackType& callback)
        {
            m_callbacks.push_back(callback);
        }
    private:
        std::vector<CallbackType> m_callbacks{};
    };

    using GenericEventSubscribers = EventSubscribers<EventCallbackFn>;
    using WindowEventSubscribers = EventSubscribers<WindowEventCallbackFn>;
    using InputEventSubscribers = EventSubscribers<InputEventCallbackFn>;
    using ApplicationEventSubscribers = EventSubscribers<ApplicationEventCallbackFn>;
    using EngineEventSubscribers = EventSubscribers<EngineEventCallbackFn>;
    using PhysicsEventSubscribers = EventSubscribers<PhysicsEventCallbackFn>;
    using GraphicsEventSubscribers = EventSubscribers<GraphicsEventCallbackFn>;
    using AudioEventSubscribers = EventSubscribers<AudioEventCallbackFn>;
    using NetworkEventSubscribers = EventSubscribers<NetworkEventCallbackFn>;
}
