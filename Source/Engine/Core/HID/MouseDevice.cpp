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

int GGE::HID::MouseDevice::GetPositionX()
{
    return s_input->GetElementState<int32>(GetDeviceKind(), ElementType(MouseElement::ePositionX));
}

int GGE::HID::MouseDevice::GetPositionY()
{
    return s_input->GetElementState<int32>(GetDeviceKind(), ElementType(MouseElement::ePositionY));
}

GGE::DisplayPosition GGE::HID::MouseDevice::GetPosition()
{
    return DisplayPosition(int(GetPositionX()), int(GetPositionY()));
}

float GGE::HID::MouseDevice::GetDeltaScroll()
{
    return s_input->GetElementState<float>(GetDeviceKind(), ElementType(MouseElement::eDeltaScroll));
}

GGE::HID::MouseButton GGE::HID::MouseDevice::GetLastPressedButton()
{
    return MouseButton(s_input->GetLastElement(GetDeviceKind()));
}
