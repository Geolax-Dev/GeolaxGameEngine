#define NOMINMAX
#include <windows.h>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <entt/entt.hpp>
#include <imgui.h>
#include <imgui_node_editor.h>
#include <Jolt/Jolt.h>
#include <crypto/cryptlib.h>

int WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR lpCmdLine,
            int nShowCmd) 
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Title", nullptr, nullptr);

    if (window) 
    {
        while (!glfwWindowShouldClose(window)) 
        {
            glfwPollEvents();

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }

        glfwDestroyWindow(window);
    }

    glfwTerminate();
    return 0;
}
