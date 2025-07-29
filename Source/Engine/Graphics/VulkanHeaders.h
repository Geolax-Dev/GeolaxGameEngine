#pragma once

#include <Core/Minimal.h>

//GUARD_EXTERNAL_INCLUDE_BEGIN
#include <volk.h>
//GUARD_EXTERNAL_INCLUDE_END

namespace GGE
{
    class VkResultWrapper
    {
    public:
        VkResultWrapper() = default;
        ~VkResultWrapper() = default;

        VkResultWrapper(VkResult vkResult) : m_vkResult(vkResult) {}

        operator VkResult() const
        {
            return m_vkResult;
        }

        operator bool() const
        {
            return IsLeastSuccessful();
        }

        bool IsLeastSuccessful() const
        {
            return static_cast<int>(m_vkResult) >= 0;
        }

        bool IsSuccessful() const
        {
            return m_vkResult == VK_SUCCESS;
        }

        String GetErrorString() const;
    private:
        VkResult m_vkResult{ VK_SUCCESS };
    };
}
