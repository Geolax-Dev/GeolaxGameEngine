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
        BasicInput() = default;
        BasicInput(const BasicInput&) = delete;
        BasicInput& operator=(const BasicInput&) = delete;
        BasicInput(BasicInput&&) noexcept = delete;
        BasicInput& operator=(BasicInput&&) noexcept = delete;

        bool OnCreate() override;

        [[maybe_unused]] static inline void ResetWindow(const Window& window)
        {
            s_window = &window;
        }

        [[maybe_unused]] static inline const Window* GetWindow()
        {
            return s_window;
        }

        bool IsPressed(KeyboardKey key) const;
        bool IsReleased(KeyboardKey key) const;
        KeyboardKey GetLastPressedKB() const;

        bool IsPressed(MouseButton btn) const;
        bool IsReleased(MouseButton btn) const;
        float GetScrollDelta() const;
        int32 GetMouseX() const;
        int32 GetMouseY() const;
        MouseButton GetLastPressedMS() const;

        bool IsPressed(GamepadButton btn) const;
        bool IsReleased(GamepadButton btn) const;
        // axes, buttons, triggers
        float GetGamepadRawValue(GamepadElement e) const;
        GamepadButton GetLastPressedGP() const;
        GamepadElement GetLastAxisGP() const;

        Element GetLastPressed(bool axes) const;
        SmallString GetLastPressedName(bool axes) const;

        bool IsCtrl(bool right = false) const;
        bool IsShift(bool right = false) const;
        bool IsAlt(bool right = false) const;
    private:
        static inline const Window* s_window{};
    };
}
