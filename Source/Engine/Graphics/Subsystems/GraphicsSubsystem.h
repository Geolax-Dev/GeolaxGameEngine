#pragma once

#include <Core/Subsystems/ISubsystem.h>
#include <Graphics/Rendering/RendererMaster.h>

namespace GGE
{
    class Window; // Forward declaration

    class GraphicsSubsystem : public ISubsystem
    {
    public:
        GraphicsSubsystem() = default;
        ~GraphicsSubsystem() override = default;

        bool OnCreateSubsystem() override;
        bool OnPostCreateSubsystem() override;
        bool OnUpdateSubsystem() override;
        void OnDestroySubsystem() override;

        static void SetCurrentWindow(std::shared_ptr<Window>);
        static std::shared_ptr<Window> GetCurrentWindow();

    private:

        static std::shared_ptr<Window> s_CurrentWindow;
    };
}
