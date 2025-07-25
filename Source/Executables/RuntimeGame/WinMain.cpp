#include <Core/Minimal.h>

#include <Core/Debug/Terminal.h>
#include <Core/ThreadPool.h>
#include <Core/HID/BasicInput.h>
#include <Core/Window.h>
#include <Core/IO/FileResourceManager.h>
#include <Core/IO/RealFileSystemProvider.h>
#include <Core/ApplicationInfo.h>
#include <Core/Configuration.h>

#include <Core/App/App.h>

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <Windows.h>
#include <GLFW/include/GLFW/glfw3.h>
GUARD_EXTERNAL_INCLUDE_END

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    // CreateApplication is implemented by following application
    auto app = GGE::CreateApplication();
    return GGE::RunApplication(app);

    //// base init

    //GGE::Debug::EnableTerminal();

    //glfwInit();

    //// filesystem init

    //GGE::IO::FileResourceManager::Create();
    //GGE::IO::FileResourceManager::Get().RegisterFileSystemProvider(
    //    std::make_shared<GGE::IO::RealFileSystemProvider>(
    //        GGE::IO::FileResourceManager::Get().GetExecutableDirectory()
    //    )
    //);
    //{
    //    const auto cachedCount = GGE::IO::FileResourceManager::Get().CacheVirtualTree(".");
    //    std::cout << "Cached " << cachedCount << " resources in the virtual tree '.'." << std::endl;
    //}

    //// visual init

    //GGE::Window ggeWindow = GGE::Configuration::CreateWindowFromConfig("Configs/Base.ini");

    //// input init

    //GGE::HID::BasicInput::ResetWindow(ggeWindow);
    //GGE::HID::BasicInput::Create();

    //// ...?

    //const GGE::String hw = "Hello World!";


    //// example of loading a resource
    //GGE::IO::RawResource resource = GGE::IO::FileResourceManager::Get().LoadSync("local/Account.xml");

    //std::cout << "Hello!";

    //// start main loop

    //while (ggeWindow.IsOpened())
    //{
    //    ggeWindow.PollOS();

    //    if (GGE::HID::BasicInput::Get().IsPressed(GGE::HID::KeyboardKey::eEscape))
    //        ggeWindow.Destroy();
    //}


    ////GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW window", nullptr, nullptr);
    ////if (window)
    ////{
    ////    
    ////    while (!glfwWindowShouldClose(window))
    ////    {
    ////        glfwPollEvents();

    ////        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    ////            glfwSetWindowShouldClose(window, GLFW_TRUE);
    ////    }

    ////    glfwDestroyWindow(window);
    ////}

    //GGE::IO::FileResourceManager::Destroy();

    //GGE::HID::BasicInput::Destroy();

    //glfwTerminate();

    //GGE::Debug::DisableTerminal();
    return 0;
}
