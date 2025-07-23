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

    enum class MouseElement : ElementType
    {
        ePositionX = int(MouseButton::eMiddle) + 1,
        ePositionY,
        eDeltaScroll
    };

    class MouseDevice : public IDevice
    {
    public:
        static bool IsButtonPressed(MouseButton button);
        static const char* GetButtonName(MouseButton button);

        static int32 GetPositionX();
        static int32 GetPositionY();
        static DisplayPosition GetPosition();
        static float GetDeltaScroll();

        static MouseButton GetLastPressedButton();

        [[maybe_unused]] static DeviceKind GetDeviceKind() { return DeviceKind::eMouse; }
    };
}
