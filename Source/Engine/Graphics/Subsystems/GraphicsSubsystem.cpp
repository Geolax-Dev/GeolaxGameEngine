#include "GraphicsSubsystem.h"

#include <Core/ApplicationInfo.h>

#include <GLFW/glfw3.h>

static std::vector<const char*> s_GetRequiredInstanceExtensions()
{
    uint32_t count = 0;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);
    std::vector<const char*> requiredExtensions(extensions, extensions + count);
    return requiredExtensions;
}

std::vector<const char*> GGE::GraphicsSubsystem::GetRequiredInstanceExtensions()
{
    static std::vector<const char*> requiredExtensions = s_GetRequiredInstanceExtensions();
    return requiredExtensions;
}

static std::vector<const char*> s_GetRequiredInstanceLayers()
{
#if !DISTRIBUTION_READY
    std::vector<const char*> requiredLayers;
    requiredLayers.push_back("VK_LAYER_KHRONOS_validation");
    return requiredLayers;
#else
    return {};
#endif
}

std::vector<const char*> GGE::GraphicsSubsystem::GetRequiredInstanceLayers()
{
    static std::vector<const char*> requiredLayers = s_GetRequiredInstanceLayers();
    return requiredLayers;
}

bool GGE::GraphicsSubsystem::InitializeVulkanInstance()
{
    GGE_LOG_INFO("Initializing Vulkan instance...");

    if (const VkResultWrapper vkResultW = volkInitialize(); !vkResultW)
    {
        GGE_LOG_ERROR("Failed to initialize Vulkan loader: {}", vkResultW.GetErrorString());
        return false;
    }

    const auto ggeAppInfo = ApplicationInfo::GetCurrent();
    const auto ggeBuildInfo = GetBuildInfo();

    VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
    appInfo.pApplicationName = ggeAppInfo.applicationName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(
        ggeAppInfo.buildInfo.Major,
        ggeAppInfo.buildInfo.Minor,
        ggeAppInfo.buildInfo.Build
    );
    appInfo.pEngineName = "GeolaxGameEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(
        ggeBuildInfo.Major,
        ggeBuildInfo.Minor,
        ggeBuildInfo.Build
    );
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instanceCreateInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    instanceCreateInfo.pApplicationInfo = &appInfo;

    auto requiredExtensions = GetRequiredInstanceExtensions();

#if !DISTRIBUTION_READY
    requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

    auto requiredLayers = GetRequiredInstanceLayers();
    instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayers.size());
    instanceCreateInfo.ppEnabledLayerNames = requiredLayers.data();

    if (const VkResultWrapper vkResultW = vkCreateInstance(&instanceCreateInfo, nullptr, &m_vkInstance); !vkResultW)
    {
        GGE_LOG_ERROR("Failed to create Vulkan instance: {}", vkResultW.GetErrorString());
        return false;
    }

    volkLoadInstance(m_vkInstance);

    GGE_LOG_INFO("Vulkan instance created successfully");

    return m_vkInstance != VK_NULL_HANDLE;
}

void GGE::GraphicsSubsystem::DestroyVulkanInstance()
{
    if (m_vkInstance)
    {
        vkDestroyInstance(m_vkInstance, nullptr);
        m_vkInstance = VK_NULL_HANDLE;
    }

    volkFinalize();
}


bool GGE::GraphicsSubsystem::OnCreateSubsystem()
{
    GGE_LOG_INFO("Creating Graphics Subsystem...");

    bool bSuccess = InitializeVulkanInstance();


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

void GGE::GraphicsSubsystem::OnDestroySubsystem()
{

    DestroyVulkanInstance();
}
