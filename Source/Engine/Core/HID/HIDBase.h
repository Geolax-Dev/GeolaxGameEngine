#pragma once

#include <Core/Minimal.h>

namespace GGE
{
    class Window;
}

namespace GGE::HID
{
    typedef uint32 Element;

    struct ElementState
    {
        float value{};

        [[maybe_unused]] ElementState() = default;
        [[maybe_unused]] ElementState(float v) noexcept : value(v) 
        { }

        [[maybe_unused]] operator float() const
        {
            return value;
        }

        static constexpr float kIdle = -1;
        static constexpr float kReleased = 0;
        static constexpr float kPressed = 1;
    };

    constexpr Element kMaxElements = 512u;
    constexpr Element kInvalidElement = uint32(-1);

    enum class DeviceKind
    {
        eNone = -1,
        eKeyboard,
        eMouse,
        eGamepad,

        COUNT
    };

    class BasicInput;

    class IDevice
    {
    public:

        static void ProvideBasicInput(const BasicInput* input);
    protected:
        static inline const Window* s_input{};
    };
}
