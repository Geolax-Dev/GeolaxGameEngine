#include "ISubsystem.h"

bool GGE::MasterSubsytem::OnCreate()
{
    return OnCreateSubsystem();
}

void GGE::MasterSubsytem::OnDestroy()
{
    OnDestroySubsystem();
}

bool GGE::MasterSubsytem::OnCreateSubsystem()
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

void GGE::MasterSubsytem::OnDestroySubsystem()
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

bool GGE::MasterSubsytem::OnUpdateSubsystem()
{
    bool bSuccess = true;

    for (auto& [_, ss] : s_subsystems)
        bSuccess &= ss->OnUpdateSubsystem();

    return bSuccess;
}
