#include "GamepadDevice.h"

#include <Core/Window.h>

bool GGE::HID::GamepadDevice::IsButtonPressed(GamepadButton button)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), ElementType(button));
}

const char* GGE::HID::GamepadDevice::GetButtonName(GamepadButton button)
{
    return s_input->GetElementName(GetDeviceKind(), ElementType(button));
}

float GGE::HID::GamepadDevice::GetRawValue(GamepadElement element)
{
    return s_input->GetElementStateF(GetDeviceKind(), ElementType(element));
}

GGE::HID::GamepadButton GGE::HID::GamepadDevice::GetLastPressedButton()
{
    return GamepadButton(s_input->GetLastElement(GetDeviceKind()));
}

GGE::HID::GamepadElement GGE::HID::GamepadDevice::GetLastUsedAxis()
{
    return GamepadElement(s_input->GetLastElement(GetDeviceKind(), true));
}
