#pragma once

#include <Core/Primitives.h>

namespace GGE
{
    class Window;
}

namespace GGE::HID
{
    typedef uint32 ElementType;

    enum class DeviceKind
    {
        eKeyboard,
        eMouse,
        eGamepad
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
