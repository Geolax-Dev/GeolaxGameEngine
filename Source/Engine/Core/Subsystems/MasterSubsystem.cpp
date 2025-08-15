#include "ISubsystem.h"

GGE::MasterSubsystem::MasterSubsystem()
{
    OnCreateSubsystem();
}

bool GGE::MasterSubsystem::OnPostCreateSubsystem()
{
    bool bSuccess = true;
    for (auto& [_, ss] : s_subsystems)
    {
        bSuccess &= ss->OnPostCreateSubsystem();
        if (!bSuccess) break;
    }

    GGE_ASSERT(bSuccess && "Failed to successfully post-initialize all registered subsystems!");
    return bSuccess;
}

GGE::MasterSubsystem::~MasterSubsystem()
{
    OnDestroySubsystem();
}

bool GGE::MasterSubsystem::OnCreateSubsystem()
{
    bool bSuccess = true;

    for (auto& [_, ss] : s_subsystems)
    {
        bSuccess &= ss->OnCreateSubsystem();
        if (!bSuccess) break;
    }

    GGE_ASSERT(bSuccess && "Failed to successfully create all registered subsystems!");

    return bSuccess;
}

void GGE::MasterSubsystem::OnDestroySubsystem()
{
    // reversed destroy

    {
        std::vector<ISubsystem*> temp;
        temp.reserve(s_subsystems.size());
        for (auto& [_, ss] : s_subsystems)
            temp.emplace_back(ss.get());

        for (auto rit = temp.rbegin(); rit != temp.rend(); ++rit)
            (*rit)->OnDestroySubsystem();
    }

    s_subsystems.clear();

}

bool GGE::MasterSubsystem::OnUpdateSubsystem()
{
    bool bSuccess = true;

    for (auto& [_, ss] : s_subsystems)
        bSuccess &= ss->OnUpdateSubsystem();

    return bSuccess;
}
