#include "KeyboardDevice.h"

#include <Core/Window.h>

bool GGE::HID::KeyboardDevice::IsKeyPressed(KeyboardKey key)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), Element(key));
}

bool GGE::HID::KeyboardDevice::IsKeyReleased(KeyboardKey key)
{
    return s_input->GetElementStateF(GetDeviceKind(), Element(key)) == ElementState::kReleased;
}

const char* GGE::HID::KeyboardDevice::GetKeyName(KeyboardKey key)
{
    return s_input->GetElementName(GetDeviceKind(), Element(key));
}

GGE::HID::KeyboardKey GGE::HID::KeyboardDevice::GetLastPressedKey()
{
    return HID::KeyboardKey(s_input->GetLastElement(GetDeviceKind()));
}

bool GGE::HID::KeyboardDevice::IsCtrl(bool right)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), Element(right ? KeyboardKey::eRightCtrl : KeyboardKey::eLeftCtrl));
}

bool GGE::HID::KeyboardDevice::IsShift(bool right)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), Element(right ? KeyboardKey::eRightShift : KeyboardKey::eLeftShift));
}

bool GGE::HID::KeyboardDevice::IsAlt(bool right)
{
    return s_input->GetElementState<bool>(GetDeviceKind(), Element(right ? KeyboardKey::eRightAlt : KeyboardKey::eLeftAlt));
}
