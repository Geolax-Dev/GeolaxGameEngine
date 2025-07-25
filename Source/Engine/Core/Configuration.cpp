#include "Configuration.h"

#include <Core/Window.h>
#include <Core/IO/FileResourceManager.h>
#include <Core/Parse/INI.h>

namespace GGE
{

    std::shared_ptr<Window> Configuration::CreateWindowFromConfig(const String& path)
    {
        std::shared_ptr<Window> window = std::make_shared<Window>();

        if (const auto iniData = IO::FileResourceManager::Get().LoadSync(path))
        {
            Parse::INIReader iniReader(iniData);

            const DisplayPosition dp = {
                iniReader.GetInteger("Window", "iPositionX", 0),
                iniReader.GetInteger("Window", "iPositionY", 0)
            };

            const DisplaySize ds = {
                iniReader.GetUnsigned("Window", "uWidth", 1280),
                iniReader.GetUnsigned("Window", "uHeight", 720)
            };

            const auto wbd = Window::WindowBuilder()
                .Title(iniReader.Get("Window", "sTitle", "GGE default window title"))
                .Position(dp)
                .Resolution(ds)
                .Fullscreen(iniReader.GetBoolean("Window", "bStartFullscreen", false))
                .Resizable(iniReader.GetBoolean("Window", "bResizable", false))
                .VerticalSync(iniReader.GetBoolean("Window", "bVSync", false))
                .Hidden(iniReader.GetBoolean("Window", "bStartHidden", false))
                .Maximized(iniReader.GetBoolean("Window", "bStartMaximized", false))
                .Build();

            GGE_ASSERT(window->Create(wbd) && "Failed to create window from .ini config!");
        }

        return window;
    }

}
