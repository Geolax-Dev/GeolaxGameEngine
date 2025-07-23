#pragma once

#include <Core/Minimal.h>
#include <Core/HID/HIDBase.h>

struct GLFWwindow;
struct GLFWmonitor;

namespace GGE
{

    class Window
    {
    public:
        struct Bits
        {
            uint32 fullscreen : 1;
            uint32 resizable : 1;
            uint32 vsync : 1;
            uint32 maximized : 1;
            uint32 hidden : 1;

            [[maybe_unused]] Bits()
                : fullscreen(0), resizable(1), vsync(1), maximized(0), hidden(0) 
            { }

        };

        class BitsBuilder
        {
        public:
            [[maybe_unused]] BitsBuilder() = default;

            [[maybe_unused]] BitsBuilder& Fullscreen(bool enable)
            {
                m_tmp.fullscreen = uint32(enable);
                return *this;
            }

            [[maybe_unused]] BitsBuilder& Resizable(bool enable)
            {
                m_tmp.resizable = uint32(enable);
                return *this;
            }

            [[maybe_unused]] BitsBuilder& VerticalSync(bool enable)
            {
                m_tmp.vsync = uint32(enable);
                return *this;
            }

            [[maybe_unused]] BitsBuilder& Maximized(bool enable)
            {
                m_tmp.maximized = uint32(enable);
                return *this;
            }

            [[maybe_unused]] BitsBuilder& Hidden(bool enable)
            {
                m_tmp.hidden = uint32(enable);
                return *this;
            }

            [[maybe_unused]] Bits Build() const { return m_tmp; }
        private:
            Bits m_tmp{};
        };

        class WindowBuilder
        {
        public:
            struct Data
            {
                String title{};
                DisplayPosition position{};
                DisplaySize size{};
                Bits bits{};
            };

            [[maybe_unused]] WindowBuilder() = default;

            [[maybe_unused]] WindowBuilder& Title(const char* pTitle)
            {
                m_tmp.title = pTitle;
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Title(const String& title)
            {
                m_tmp.title = title;
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Position(const DisplayPosition& pos)
            {
                m_tmp.position = pos;
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Position(int32 x, int32 y)
            {
                m_tmp.position = { x, y };
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Resolution(const DisplaySize& size)
            {
                m_tmp.size = size;
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Resolution(uint32 width, uint32 height)
            {
                m_tmp.size = { width, height };
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Fullscreen(bool enable)
            {
                m_tmp.bits.fullscreen = uint32(enable);
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Resizable(bool enable)
            {
                m_tmp.bits.resizable = uint32(enable);
                return *this;
            }

            [[maybe_unused]] WindowBuilder& VerticalSync(bool enable)
            {
                m_tmp.bits.vsync = uint32(enable);
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Maximized(bool enable)
            {
                m_tmp.bits.maximized = uint32(enable);
                return *this;
            }

            [[maybe_unused]] WindowBuilder& Hidden(bool enable)
            {
                m_tmp.bits.hidden = uint32(enable);
                return *this;
            }

            [[maybe_unused]] Data Build() const
            {
                return m_tmp;
            }

        private:
            Data m_tmp{};
        };

        [[maybe_unused]] Window();

        [[maybe_unused]] Window(
            const String& title,
            DisplayPosition position,
            DisplaySize size,
            Bits bits
        );

        [[maybe_unused]] Window(const WindowBuilder::Data& wbd);

        [[maybe_unused]] ~Window();

        [[maybe_unused]] bool Create(
            const String& title,
            DisplayPosition position,
            DisplaySize size,
            Bits bits
        );

        [[maybe_unused]] bool Create(const WindowBuilder::Data& wbd);

        [[maybe_unused]] void Destroy();

        [[maybe_unused]] void Hide(bool completely = false);

        [[maybe_unused]] void Show();

        [[maybe_unused]] void ShowMaximized();

        [[maybe_unused]] void MakeFullscreen();

        [[maybe_unused]] void MakeFullscreen(DisplaySize);

        [[maybe_unused]] void MakeFullscreen(uint32, uint32);

        [[maybe_unused]] void MakeNormal();

        [[maybe_unused]] const String& GetTitle() const { return m_title; }

        [[maybe_unused]] GLFWwindow* GetGLFW() const { return m_windowHandle; }

        [[maybe_unused]] DisplayPosition GetPosition() const { return m_position; }

        [[maybe_unused]] int32 GetX() const { return m_position.x; }

        [[maybe_unused]] int32 GetY() const { return m_position.y; }

        [[maybe_unused]] DisplaySize GetSize() const { return m_size; }

        [[maybe_unused]] uint32 GetWidth() const { return m_size.width; }

        [[maybe_unused]] uint32 GetHeight() const { return m_size.height; }

        [[maybe_unused]] bool IsFullscreen() const { return bool(m_bits.fullscreen); }

        [[maybe_unused]] bool IsResizable() const { return bool(m_bits.resizable); }

        [[maybe_unused]] bool IsVSync() const { return bool(m_bits.vsync); }

        [[maybe_unused]] bool IsMaximized() const { return bool(m_bits.maximized); }

        [[maybe_unused]] bool IsHidden() const { return bool(m_bits.hidden); }

        [[maybe_unused]] bool IsOpened() const { return m_opened; }

        [[maybe_unused]] void PollOS();

        [[maybe_unused]] HID::ElementType GetLastElement(HID::DeviceKind dk, bool gamepadAxis = false) const
        {
            return s_inputState->lastWrite[int(dk)][int(gamepadAxis)];
        }

        [[maybe_unused]] float GetElementStateF(HID::DeviceKind dk, HID::ElementType et) const
        {
            return s_inputState->elems[int(dk)][int(et)];
        }

        [[maybe_unused]] static const char* GetElementName(HID::DeviceKind, HID::ElementType);

        template<class T>
        [[maybe_unused]] T GetElementState(HID::DeviceKind dk, HID::ElementType et) const
        {
            return static_cast<T>(GetElementStateF(dk, et));
        }

        template<>
        [[maybe_unused]] bool GetElementState<bool>(HID::DeviceKind dk, HID::ElementType et) const
        {
            return GetElementStateF(dk, et) == 1.f;
        }
    private:
        String m_title{};
        GLFWwindow* m_windowHandle{};
        GLFWmonitor* m_monitorHandle{};
        DisplayPosition m_position{};
        DisplaySize m_size{};
        Bits m_bits{};
        bool m_opened{};

    private:
        struct InputStateType
        {
            HID::ElementState elems[int(HID::DeviceKind::COUNT)][HID::kMaxElements];
            HID::ElementType lastWrite[int(HID::DeviceKind::COUNT)][2]{};

            InputStateType();
        };

        static inline InputStateType *s_inputState{};
    };

}
