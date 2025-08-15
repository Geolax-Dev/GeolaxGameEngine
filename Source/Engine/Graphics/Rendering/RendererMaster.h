#pragma once

#include <Core/Singleton.h>

#include "Camera.h"
#include "IRenderer.h"

namespace GGE
{
    class RendererMaster : public Singleton<RendererMaster>
    {
    public:
        using RenderersList = std::initializer_list<std::unique_ptr<IRenderer>>;

        RendererMaster(bgfx::RendererType::Enum, std::shared_ptr<Window>, RenderersList);
        ~RendererMaster() override;

        // TODO: add options for initialization
        bool Initialize();  // Phase1: basic initialization
        bool Setup();       // Phase2: pre-mainloop

        bool FrameBegin();
        void FrameDraw();
        void FrameEndAndPresent();

        void OnWindowResized();
        void EnableRendering(bool enable) noexcept { m_enabledRendering = enable; }

    public:
        CameraControl& Cameras() { return *m_cameraControl; }
        uint2 GetViewportSize() const { return { m_window->GetWidth(), m_window->GetHeight() }; }

    private:
        std::vector<std::unique_ptr<IRenderer>> m_renderers{};
        std::shared_ptr<Window> m_window{};
        std::unique_ptr<CameraControl> m_cameraControl{};

        bool m_enabledRendering{ true };
    };
}
