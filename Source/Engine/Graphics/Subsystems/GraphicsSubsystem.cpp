#include "GraphicsSubsystem.h"
#include <Core/Window.h>

#include <Graphics/Rendering/RendererMaster.h>

namespace GGE
{
    std::shared_ptr<Window> GraphicsSubsystem::s_CurrentWindow = {};
}

bool GGE::GraphicsSubsystem::OnCreateSubsystem()
{
    return true;
}

bool GGE::GraphicsSubsystem::OnPostCreateSubsystem()
{
    GGE_LOG_INFO("Creating Graphics Subsystem...");

    bool bSuccess = true;

    RendererMaster::Create(bgfx::RendererType::OpenGL, s_CurrentWindow, RendererMaster::RenderersList{});
    auto& rr = RendererMaster::Get();

    bSuccess &= rr.Initialize();

    bSuccess &= rr.Setup();

    s_CurrentWindow->GetEventSubscribers() += [](WindowEvent& wevent)
        {
            if (wevent.GetEventType() == WindowEvents_WindowResize)
            {
                auto& rr = RendererMaster::Get();

                const WindowResizeEvent& resizeEvent = static_cast<const WindowResizeEvent&>(wevent);
                GGE_LOG_INFO("Window resized to {}x{}", resizeEvent.width, resizeEvent.height);

                const bool disabledRendering = (resizeEvent.width == 0) || (resizeEvent.height == 0);
                if (disabledRendering)
                {
                    GGE_LOG_DEBUG("Rendering disabled!");
                }

                rr.OnWindowResized();
                rr.EnableRendering(!disabledRendering);
            }
        };

    if (bSuccess)
    {
        GGE_LOG_INFO("Graphics Subsystem created successfully");
    }
    else
    {
        GGE_LOG_ERROR("Failed to create Graphics Subsystem");
    }

    return bSuccess;
}

size_t gc = 0;

bool GGE::GraphicsSubsystem::OnUpdateSubsystem()
{
    auto& rr = RendererMaster::Get();
    if (rr.FrameBegin())
    {
        rr.FrameDraw();
        rr.FrameEndAndPresent();
    }
    return true;
}

void GGE::GraphicsSubsystem::OnDestroySubsystem()
{
    GGE_LOG_INFO("Destroying Graphics Subsystem...");

    RendererMaster::Destroy();
}

void GGE::GraphicsSubsystem::SetCurrentWindow(std::shared_ptr<Window> w)
{
    s_CurrentWindow = w;
}

std::shared_ptr<GGE::Window> GGE::GraphicsSubsystem::GetCurrentWindow()
{
    return s_CurrentWindow;
}
