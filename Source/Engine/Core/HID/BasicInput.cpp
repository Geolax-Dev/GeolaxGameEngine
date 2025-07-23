#include "BasicInput.h"

bool GGE::HID::BasicInput::OnCreate()
{
    KeyboardDevice::ProvideBasicInput(this);
    MouseDevice::ProvideBasicInput(this);
    GamepadDevice::ProvideBasicInput(this);

    return true;
}
