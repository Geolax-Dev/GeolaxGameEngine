#include <Core/Minimal.h>

#include <Core/ThreadPool.h>
#include <Core/HID/BasicInput.h>

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
    glfwInit();

    GGE::HID::BasicInput::Create();

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW window", nullptr, nullptr);
    if (window)
    {
        
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glfwDestroyWindow(window);
    }

    GGE::HID::BasicInput::Destroy();

    glfwTerminate();
    return 0;
}
