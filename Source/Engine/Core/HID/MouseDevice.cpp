#include "MouseDevice.h"

#include <Core/Window.h>

bool GGE::HID::MouseDevice::IsButtonPressed(MouseButton button)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), ElementType(button));
}

const char* GGE::HID::MouseDevice::GetButtonName(MouseButton button)
{
    return s_input->GetElementName(GetDeviceKind(), ElementType(button));
}
