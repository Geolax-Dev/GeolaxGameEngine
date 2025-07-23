#pragma once

#include <Core/Minimal.h>

namespace GGE
{
    class Window;
}

namespace GGE::HID
{
    typedef uint32 ElementType;

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

        static constexpr float eIdle = -1;
        static constexpr float eReleased = 0;
        static constexpr float ePressed = 1;
    };

    constexpr ElementType kMaxElements = 512u;

    enum class DeviceKind
    {
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
