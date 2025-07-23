#pragma once

#include <Core/HID/HIDBase.h>

namespace GGE::HID
{
    enum class MouseButton : ElementType
    {
        eLeft,
        eRight,
        eMiddle,
    };

    class MouseDevice : public IDevice
    {
    public:
        static bool IsButtonPressed(MouseButton button);
        static const char* GetButtonName(MouseButton button);

        [[maybe_unused]] static DeviceKind GetDeviceKind() { return DeviceKind::eMouse; }
    };
}
