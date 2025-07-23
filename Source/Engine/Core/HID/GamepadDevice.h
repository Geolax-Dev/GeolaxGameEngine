#pragma once

#include <Core/HID/HIDBase.h>

namespace GGE::HID
{

    enum class GamepadElement : ElementType
    {
        eA,
        eB,
        eX,
        eY,
        eLeftBumper,
        eRightBumper,
        eBack,
        eStart,
        eGuide,
        eLeftThumb,
        eRightThumb,
        eDpadUp,
        eDpadRight,
        eDpadDown,
        eDpadLeft,

        // Get by GetRawValue!
        eLeftX,
        // Get by GetRawValue!
        eLeftY,
        // Get by GetRawValue!
        eRightX,
        // Get by GetRawValue!
        eRightY,
        // Get by GetRawValue!
        eLeftTrigger,
        // Get by GetRawValue!
        eRightTrigger,

        eCross    = eA,
        eCircle   = eB,
        eSquare   = eX,
        eTriangle = eY,
    };

    typedef GamepadElement GamepadButton;

    class GamepadDevice : public IDevice
    {
    public:
        static bool IsButtonPressed(GamepadButton button);
        static const char* GetButtonName(GamepadButton button);

        static float GetRawValue(GamepadElement element);

        static GamepadButton GetLastPressedButton();
        static GamepadElement GetLastUsedAxis();

        [[maybe_unused]] static DeviceKind GetDeviceKind() { return DeviceKind::eGamepad; }
    };

}
