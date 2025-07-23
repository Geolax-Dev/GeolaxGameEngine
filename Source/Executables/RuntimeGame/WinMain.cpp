#include <Core/Minimal.h>

#include <Core/Debug/Terminal.h>
#include <Core/ThreadPool.h>
#include <Core/HID/BasicInput.h>
#include <Core/Window.h>

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
    GGE::Debug::EnableTerminal();

    glfwInit();

    GGE::Window ggeWindow;

    ggeWindow.Create(
        GGE::Window::WindowBuilder()
        .Title("GGE Window")
        .Position(100, 100)
        .Resolution(1280, 720)
        .Fullscreen(false)
        .Resizable(true)
        .VerticalSync(true)
        .Build()
    );

    GGE::HID::BasicInput::ResetWindow(ggeWindow);
    GGE::HID::BasicInput::Create();

    std::cout << "Hello!";

    while (ggeWindow.IsOpened())
    {
        ggeWindow.PollOS();

        //if (const auto e = GGE::HID::KeyboardDevice::GetLastPressedKey(); e != GGE::HID::KeyboardKey::eUnknown)
        //{
        //    const GGE::SmallString s = GGE::HID::KeyboardDevice::GetKeyName(e);
        //    GGE::Debug::WriteTerminal(s.c_str(), s.size());
        //}

        if (GGE::HID::KeyboardDevice::IsKeyPressed(GGE::HID::KeyboardKey::eEscape))
            ggeWindow.Destroy();
    }


    //GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW window", nullptr, nullptr);
    //if (window)
    //{
    //    
    //    while (!glfwWindowShouldClose(window))
    //    {
    //        glfwPollEvents();

    //        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //            glfwSetWindowShouldClose(window, GLFW_TRUE);
    //    }

    //    glfwDestroyWindow(window);
    //}

    GGE::HID::BasicInput::Destroy();

    glfwTerminate();

    GGE::Debug::DisableTerminal();
    return 0;
}
