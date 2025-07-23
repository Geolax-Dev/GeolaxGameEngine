#include "KeyboardDevice.h"

#include <Core/Window.h>

bool GGE::HID::KeyboardDevice::IsKeyPressed(KeyboardKey key)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), ElementType(key));
}

const char* GGE::HID::KeyboardDevice::GetKeyName(KeyboardKey key)
{
    return s_input->GetElementName(GetDeviceKind(), ElementType(key));
}
