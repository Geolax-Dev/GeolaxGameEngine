#pragma once

#include <Core/App/App.h>

namespace GGE
{
    class Window;

    class RuntimeApp : public IApp
    {
    public:
        RuntimeApp();
        ~RuntimeApp() override;

        bool Create() override;
        bool Run() override;
        void Destroy() override;

        std::shared_ptr<Window> GetWindow() const
        {
            return m_window;
        }

        bool IsRunning() const
        {
            return m_running;
        }

        void Exit()
        {
            m_running = false;
        }

        bool InitializeGlfw();
        void ShutdownGlfw();
    private:
        std::shared_ptr<Window> m_window{};
        bool m_running{};
    };
}
