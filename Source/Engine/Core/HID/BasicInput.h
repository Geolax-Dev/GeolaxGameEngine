#pragma once

#include <Core/Singleton.h>

#include <Core/HID/KeyboardDevice.h>
#include <Core/HID/MouseDevice.h>
#include <Core/HID/GamepadDevice.h>

namespace GGE
{
    class Window;
}

namespace GGE::HID
{
    class BasicInput : public Singleton<BasicInput>
    {
    public:
        bool OnCreate() override;

        [[maybe_unused]] static inline void ResetWindow(const Window& window)
        {
            s_window = &window;
        }

        [[maybe_unused]] static inline const Window* GetWindow()
        {
            return s_window;
        }
    private:
        static inline const Window* s_window{};
    };
}
