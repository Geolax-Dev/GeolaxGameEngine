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
