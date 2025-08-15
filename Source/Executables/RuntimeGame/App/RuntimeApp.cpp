#include "RuntimeApp.h"

#include <GLFW/include/GLFW/glfw3.h>

#include <Core/Subsystems/ISubsystem.h>
#include <Core/Subsystems/BasicsSubsystem.h>
#include <Core/Configuration.h>
#include <Core/HID/BasicInput.h>

#include <Graphics/Subsystems/GraphicsSubsystem.h>

#include <Graphics/bgfx-link.h>

namespace GGE
{

    GGE::RuntimeApp::RuntimeApp()
    {
    }

    RuntimeApp::~RuntimeApp()
    {
    }

    bool RuntimeApp::Create()
    {
        if (InitializeGlfw())
        {
            MasterSubsystem::Get().RegisterSubsystem<BasicsSubsystem>();
            MasterSubsystem::Get().RegisterSubsystem<GraphicsSubsystem>();
            MasterSubsystem::Create();

            m_window = Configuration::CreateWindowFromConfig();
            if (!m_window->IsOpened())
            {
                GGE_LOG_CRITICAL("Failed to create window from config");
                return false;
            }

            GraphicsSubsystem::SetCurrentWindow(m_window);

            if (!MasterSubsystem::Get().OnPostCreateSubsystem())
            {
                GGE_LOG_CRITICAL("Failed to post-initialize GraphicsSubsystem");
                return false;
            }

            HID::BasicInput::ResetWindow(*m_window);
            HID::BasicInput::Create();

            

            m_running = true;
        }
        return m_running;
    }

    bool RuntimeApp::Run()
    {
        bool iterationWasOk = m_running;
        
        while (m_running && iterationWasOk)
        {
            if (!m_window->IsOpened())
            {
                Exit();
                continue;
            }

            if (HID::BasicInput::Get().IsPressed(HID::KeyboardKey::eEscape))
            {
                Exit();
                continue;
            }

            iterationWasOk &= MasterSubsystem::Get().OnUpdateSubsystem();

            m_window->PollOS();
        }

        return iterationWasOk;
    }

    void RuntimeApp::Destroy()
    {

        HID::BasicInput::Destroy();

        m_window->Destroy();
        m_window.reset();

        MasterSubsystem::Destroy();
        ShutdownGlfw();
    }

    bool RuntimeApp::InitializeGlfw()
    {
        return glfwInit() == GLFW_TRUE;
    }

    void RuntimeApp::ShutdownGlfw()
    {
        glfwTerminate();
    }



    
    std::shared_ptr<IApp> CreateApplication()
    {
        return std::make_shared<RuntimeApp>();
    }
}
