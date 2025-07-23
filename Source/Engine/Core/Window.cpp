#include "Window.h"

#include <Core/HID/GamepadDevice.h>
#include <Core/HID/KeyboardDevice.h>
#include <Core/HID/MouseDevice.h>

#include <GLFW/glfw3.h>

#ifdef _WIN32
#undef APIENTRY
#include <windows.h>
#endif

namespace GGE
{
    static double s_scrollDelta{};

#ifdef _WIN32
    // Returns a pointer to a static buffer containing the key name.
    // Returns an empty string if the scan code isn’t recognized.
    const char* ScanCodeToString(int scanCode) {
        static char keyName[128] = {0};

        // Build the lParam for GetKeyNameText:
        //  bits 16–23: the scan code
        //  bit  24   : extended-key flag
        LONG lParam = LONG(scanCode << 16);

        // Detect common “extended” keys and set bit 24
        // (e.g. right Ctrl, right Alt, keypad Divide, arrow keys, etc.)
        UINT vk = MapVirtualKey(UINT(scanCode), MAPVK_VSC_TO_VK_EX);
        switch (vk) {
            case VK_RCONTROL:
            case VK_RMENU:     // right ALT
            case VK_DIVIDE:    // numpad “/”
            case VK_HOME: case VK_UP: case VK_PRIOR: case VK_LEFT:
            case VK_RIGHT: case VK_END: case VK_DOWN: case VK_NEXT:
            case VK_INSERT: case VK_DELETE:
                lParam |= 1 << 24;
                break;
            default:
                break;
        }

        // Ask Windows for the localized name
        int len = GetKeyNameTextA(lParam, keyName, sizeof(keyName));
        if (len > 0) {
            // keyName is already null-terminated
            return keyName;
        }

        // Fallback: unrecognized scan code
        return "";
    }
#endif

    static inline bool _CreateGlfwWindow(const String& title, DisplayPosition pos, DisplaySize sz, Window::Bits bits, GLFWwindow*& window)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, int(bits.resizable));
        glfwWindowHint(GLFW_MAXIMIZED, int(bits.maximized));
        glfwWindowHint(GLFW_POSITION_X, pos.x);
        glfwWindowHint(GLFW_POSITION_Y, pos.y);
        glfwWindowHint(GLFW_VISIBLE, int(1u - bits.hidden));

        GLFWmonitor* monitor = bits.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        GLFWwindow* sharedWindow = nullptr;

        window = glfwCreateWindow(int(sz.width), int(sz.height), title.c_str(), monitor, sharedWindow);

        if (window)
        { 
            glfwSetScrollCallback(window, [](GLFWwindow*, double x, double y) { s_scrollDelta = y; });
        }

        return window != nullptr;
    }

    Window::Window()
        : m_monitorHandle(glfwGetPrimaryMonitor())
    {
        if (!s_inputState)
            s_inputState = new InputStateType{};
    }

    Window::Window(const String& title, DisplayPosition position, DisplaySize size, Bits bits)
    {
        GGE_ASSERT(Create(title, position, size, bits) && "Window creation (constructor) failed!");
    }

    Window::Window(const WindowBuilder::Data& wbd)
    {
        GGE_ASSERT(Create(wbd) && "Window creation (constructor) failed!");
    }

    Window::~Window()
    {
        Destroy();
    }

    bool Window::Create(const String& title, DisplayPosition position, DisplaySize size, Bits bits)
    {
        m_title = title;
        m_position = position;
        m_size = size;
        m_bits = bits;
        if (_CreateGlfwWindow(m_title, m_position, m_size, m_bits, m_windowHandle))
        {
            glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window) 
                {
                    Window& w = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
                    w.Destroy();
                });

            glfwSetWindowUserPointer(m_windowHandle, this);

            m_opened = true;
        }
        return m_opened;
    }

    bool Window::Create(const WindowBuilder::Data& wbd)
    {
        return Create(wbd.title, wbd.position, wbd.size, wbd.bits);
    }

    void Window::Destroy()
    {
        m_opened = false;

        if (m_windowHandle)
        {
            glfwDestroyWindow(m_windowHandle);
            m_windowHandle = nullptr;
        }
    }

    void Window::Hide(bool completely)
    {
        if (completely)
        {
            glfwHideWindow(m_windowHandle);
        }
        else
        {
            glfwIconifyWindow(m_windowHandle);
        }

        m_bits.hidden = true;
    }

    void Window::Show()
    {
        glfwShowWindow(m_windowHandle);

        m_bits.hidden = false;
    }

    void Window::ShowMaximized()
    {
        glfwShowWindow(m_windowHandle);
        glfwMaximizeWindow(m_windowHandle);

        m_bits.hidden = false;
        m_bits.maximized = true;
    }

    void Window::MakeFullscreen()
    {
        MakeFullscreen(m_size);
    }

    void Window::MakeFullscreen(DisplaySize sz)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(m_monitorHandle);
        glfwSetWindowMonitor(m_windowHandle, m_monitorHandle, 0, 0, int(sz.width), int(sz.height), mode->refreshRate);

        m_bits.hidden = false;
        m_bits.fullscreen = true;
    }

    void Window::MakeFullscreen(uint32 width, uint32 height)
    {
        MakeFullscreen(DisplaySize(width, height));
    }

    void Window::MakeNormal()
    {
        const GLFWvidmode* mode = glfwGetVideoMode(m_monitorHandle);
        glfwSetWindowMonitor(m_windowHandle, nullptr, 0, 0, int(m_size.width), int(m_size.height), mode->refreshRate);

        m_bits.hidden = false;
        m_bits.fullscreen = false;
    }

    void Window::PollOS()
    {
        {   // gather keyboard input state
            auto& kbd = s_inputState->elems[int(HID::DeviceKind::eKeyboard)];
            auto& lw = s_inputState->lastWrite[int(HID::DeviceKind::eKeyboard)][0];

            for (int key = GLFW_KEY_SPACE; key < GLFW_KEY_LAST; ++key)
            {
                // key state
                auto& kstate = kbd[key];

                switch (glfwGetKey(m_windowHandle, key))
                {
                    case GLFW_PRESS:
                    {
                        kstate = HID::ElementState::ePressed;
                        lw = HID::ElementType(key);
                    } break;

                    case GLFW_RELEASE:
                    {
                        if (kstate != HID::ElementState::eIdle)
                        {
                            if (kstate == HID::ElementState::ePressed)
                            {
                                kstate = HID::ElementState::eReleased;
                                lw = HID::ElementType(key);
                            }
                            else
                            {
                                kstate = HID::ElementState::eIdle;
                                lw = HID::ElementType(key);
                            }
                        }
                    } break;
                }
            }
        }

        {   // gather mouse input state
            auto& ms = s_inputState->elems[int(HID::DeviceKind::eMouse)];
            auto& lw = s_inputState->lastWrite[int(HID::DeviceKind::eMouse)][0];

            {
                double xpos, ypos;
                glfwGetCursorPos(m_windowHandle, &xpos, &ypos);

                ms[int(HID::MouseElement::ePositionX)] = HID::ElementState(float(xpos));
                ms[int(HID::MouseElement::ePositionY)] = HID::ElementState(float(ypos));
                ms[int(HID::MouseElement::eDeltaScroll)] = HID::ElementState(float(s_scrollDelta));
            }

            const int buttons[] = {
                GLFW_MOUSE_BUTTON_LEFT,
                GLFW_MOUSE_BUTTON_RIGHT,
                GLFW_MOUSE_BUTTON_MIDDLE
            };

            for (auto btn : buttons)
            {
                auto& kstate = ms[btn];

                switch (glfwGetMouseButton(m_windowHandle, btn))
                {
                    case GLFW_PRESS:
                    {
                        kstate = HID::ElementState::ePressed;
                        lw = HID::ElementType(btn);
                    } break;

                    case GLFW_RELEASE:
                    {
                        if (kstate != HID::ElementState::eIdle)
                        {
                            if (kstate == HID::ElementState::ePressed)
                            {
                                kstate = HID::ElementState::eReleased;
                                lw = HID::ElementType(btn);
                            }
                            else
                            {
                                kstate = HID::ElementState::eIdle;
                                lw = HID::ElementType(btn);
                            }
                        }
                    } break;
                }
            }

        }

        { // gather gamepad input
            for (int gamepadIndex = GLFW_JOYSTICK_1; gamepadIndex < GLFW_JOYSTICK_LAST; ++gamepadIndex)
            {
                if (glfwJoystickIsGamepad(gamepadIndex))
                {
                    auto& gp = s_inputState->elems[int(HID::DeviceKind::eGamepad)];
                    auto& lw = s_inputState->lastWrite[int(HID::DeviceKind::eGamepad)];

                    GLFWgamepadstate state;
                    if (glfwGetGamepadState(gamepadIndex, &state))
                    {
                        for (int key = int(HID::GamepadButton::eA); key < int(HID::GamepadButton::eDpadLeft); ++key)
                        {
                            auto& kstate = gp[key];

                            switch (state.buttons[key])
                            {
                            case GLFW_PRESS:
                            {
                                kstate = HID::ElementState::ePressed;
                                lw[0] = HID::ElementType(key);
                            } break;

                            case GLFW_RELEASE:
                            {
                                if (kstate != HID::ElementState::eIdle)
                                {
                                    if (kstate == HID::ElementState::ePressed)
                                    {
                                        kstate = HID::ElementState::eReleased;
                                        lw[0] = HID::ElementType(key);
                                    }
                                    else
                                    {
                                        kstate = HID::ElementState::eIdle;
                                        lw[0] = HID::ElementType(key);
                                    }
                                }
                            } break;
                            }
                        }

                        for (int axis = int(HID::GamepadElement::eLeftX); axis < int(HID::GamepadElement::eRightTrigger); ++axis)
                        {
                            gp[axis] = state.axes[axis - int(HID::GamepadButton::eDpadLeft)];
                            lw[1] = HID::ElementType(axis);
                        }
                    }

                    break;
                }
            }
        }

        glfwPollEvents();
    }

    const char* Window::GetElementName(HID::DeviceKind dk, HID::ElementType et)
    {
        switch (dk)
        {
            case HID::DeviceKind::eKeyboard:
            {
                const auto kn = glfwGetKeyName(int(et), int(et));
                return kn ? kn : ScanCodeToString(glfwGetKeyScancode(int(et)));
            }

            case HID::DeviceKind::eMouse:
            {
                switch (et)
                {
                    case static_cast<HID::ElementType>(HID::MouseButton::eLeft): return "LMB";
                    case static_cast<HID::ElementType>(HID::MouseButton::eRight): return "RMB";
                    case static_cast<HID::ElementType>(HID::MouseButton::eMiddle): return "MMB";
                }
            }

            case HID::DeviceKind::eGamepad:
            {
                switch (et)
                {
                    case static_cast<HID::ElementType>(HID::GamepadElement::eA): return "A";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eB): return "B";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eX): return "X";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eY): return "Y";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eLeftBumper): return "LeftBumper";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eRightBumper): return "RightBumper";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eBack): return "Back";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eStart): return "Start";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eGuide): return "Guide";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eLeftThumb): return "LeftThumb";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eRightThumb): return "RightThumb";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eDpadUp): return "DpadUp";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eDpadRight): return "DpadRight";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eDpadDown): return "DpadDown";
                    case static_cast<HID::ElementType>(HID::GamepadElement::eDpadLeft): return "DpadLeft";
                }
            }

            case HID::DeviceKind::COUNT:
            default:
                break;
        }

        return "(null)";
    }

    Window::InputStateType::InputStateType()
    {
        for (auto& elms : elems)
        {
            std::fill_n(elms, std::size(elms), HID::ElementState::eIdle);
        }
    }

}
