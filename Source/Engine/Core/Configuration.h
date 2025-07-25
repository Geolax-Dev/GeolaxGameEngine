#pragma once

#include <Core/Minimal.h>

namespace GGE
{
    class Window;

    class Configuration
    {
    public:

        static std::shared_ptr<Window> CreateWindowFromConfig(const String& path = "Configs/Base.ini");
    };
}
