#pragma once

#include <Core/Minimal.h>

namespace GGE
{
    class IApp
    {
    public:
        virtual ~IApp() = default;

        // returns true of success
        virtual bool Create() = 0;
        virtual bool Run() = 0;
        virtual void Destroy() = 0;
    };

    std::shared_ptr<IApp> CreateApplication();
    int32 RunApplication(std::shared_ptr<IApp> app);
}
