#include "BasicsSubsystem.h"

#include <Core/Debug/Terminal.h>
#include <Core/IO/RealFileSystemProvider.h>

bool GGE::BasicsSubsystem::OnCreateSubsystem()
{
    Debug::EnableTerminal();

    IO::FileResourceManager::Create();
    IO::FileResourceManager::Get().RegisterFileSystemProvider(
        std::make_shared<IO::RealFileSystemProvider>(
            IO::FileResourceManager::Get().GetExecutableDirectory()
        )
    );
    {
        const auto cachedCount = IO::FileResourceManager::Get().CacheVirtualTree(".");
        std::cout << "Cached " << cachedCount << " resources in the virtual tree '.'." << std::endl;
    }

    return true;
}

void GGE::BasicsSubsystem::OnDestroySubsystem()
{
    IO::FileResourceManager::Destroy();
    Debug::DisableTerminal();
}
