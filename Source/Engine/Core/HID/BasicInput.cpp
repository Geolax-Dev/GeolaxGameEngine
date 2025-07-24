#include "BasicInput.h"

bool GGE::HID::BasicInput::OnCreate()
{
    KeyboardDevice::ProvideBasicInput(this);
    MouseDevice::ProvideBasicInput(this);
    GamepadDevice::ProvideBasicInput(this);

    return true;
}

bool GGE::HID::BasicInput::IsPressed(KeyboardKey key) const
{
    return KeyboardDevice::IsKeyPressed(key);
}

bool GGE::HID::BasicInput::IsReleased(KeyboardKey key) const
{
    return KeyboardDevice::IsKeyReleased(key);
}

GGE::HID::KeyboardKey GGE::HID::BasicInput::GetLastPressedKB() const
{
    return KeyboardDevice::GetLastPressedKey();
}

bool GGE::HID::BasicInput::IsPressed(MouseButton btn) const
{
    return MouseDevice::IsButtonPressed(btn);
}

bool GGE::HID::BasicInput::IsReleased(MouseButton btn) const
{
    return MouseDevice::IsButtonReleased(btn);
}

float GGE::HID::BasicInput::GetScrollDelta() const
{
    return MouseDevice::GetDeltaScroll();
}

GGE::int32 GGE::HID::BasicInput::GetMouseX() const
{
    return MouseDevice::GetPositionX();
}

GGE::int32 GGE::HID::BasicInput::GetMouseY() const
{
    return MouseDevice::GetPositionY();
}

GGE::HID::MouseButton GGE::HID::BasicInput::GetLastPressedMS() const
{
    return MouseDevice::GetLastPressedButton();
}

bool GGE::HID::BasicInput::IsPressed(GamepadButton btn) const
{
    return GamepadDevice::IsButtonPressed(btn);
}

bool GGE::HID::BasicInput::IsReleased(GamepadButton btn) const
{
    return GamepadDevice::IsButtonReleased(btn);
}

float GGE::HID::BasicInput::GetGamepadRawValue(GamepadElement e) const
{
    return GamepadDevice::GetRawValue(e);
}

GGE::HID::GamepadButton GGE::HID::BasicInput::GetLastPressedGP() const
{
    return GamepadDevice::GetLastPressedButton();
}

GGE::HID::GamepadElement GGE::HID::BasicInput::GetLastAxisGP() const
{
    return GamepadDevice::GetLastUsedAxis();
}

GGE::HID::Element GGE::HID::BasicInput::GetLastPressed(bool axes) const
{
    return s_window->GetLastElement(axes);
}

GGE::SmallString GGE::HID::BasicInput::GetLastPressedName(bool axes) const
{
    if (const auto deviceKind = s_window->GetLastUsedDeviceKind(); deviceKind != DeviceKind::eNone)
        return s_window->GetElementName(deviceKind, s_window->GetLastElement(axes));

    return "(null)";
}

bool GGE::HID::BasicInput::IsCtrl(bool right) const
{
    return KeyboardDevice::IsCtrl(right);
}

bool GGE::HID::BasicInput::IsShift(bool right) const
{
    return KeyboardDevice::IsShift(right);
}

bool GGE::HID::BasicInput::IsAlt(bool right) const
{
    return KeyboardDevice::IsAlt(right);
}
