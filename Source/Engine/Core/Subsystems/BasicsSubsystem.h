#pragma once

#include <Core/Subsystems/ISubsystem.h>

namespace GGE
{
    class BasicsSubsystem : public ISubsystem
    {
    public:
        BasicsSubsystem() = default;
        ~BasicsSubsystem() override = default;

        bool OnCreateSubsystem() override;
        void OnDestroySubsystem() override;

    private:
        bool SetupSpdlog();
        void ShutdownSpdlog();
    };
}
