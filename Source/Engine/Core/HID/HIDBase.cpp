#include "HIDBase.h"

#include "BasicInput.h"

void GGE::HID::IDevice::ProvideBasicInput(const BasicInput* input)
{
    s_input = input->GetWindow();
}
