#pragma once

#include <Core/Subsystems/ISubsystem.h>
#include <Graphics/VulkanHeaders.h>

namespace GGE
{
    class GraphicsSubsystem : public ISubsystem
    {
    public:
        GraphicsSubsystem() = default;
        ~GraphicsSubsystem() override = default;

        bool OnCreateSubsystem() override;
        void OnDestroySubsystem() override;

        static std::vector<const char*> GetRequiredInstanceExtensions();
        static std::vector<const char*> GetRequiredInstanceLayers();

        VkInstance GetVkInstance() const
        {
            return m_vkInstance;
        }
    private:
        VkInstance m_vkInstance{ VK_NULL_HANDLE };

        bool InitializeVulkanInstance();
        void DestroyVulkanInstance();
    };
}
