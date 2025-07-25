#pragma once

#include <Core/Minimal.h>
#include <Core/Singleton.h>

namespace GGE
{
    class ISubsystem
    {
    public:
        virtual ~ISubsystem() = default;

        virtual bool OnCreateSubsystem() = 0;
        virtual void OnDestroySubsystem() = 0;
        virtual bool OnUpdateSubsystem() { return true; }
    };

    class MasterSubsytem : public ISubsystem, public Singleton<MasterSubsytem>
    {
    public:
        MasterSubsytem() = default;
        ~MasterSubsytem() override = default;

        bool OnCreate() override;
        void OnDestroy() override;

        bool OnUpdateSubsystem() override;

        template<class SubsystemClass>
        void RegisterSubsystem()
        {
            s_subsystems[typeid(SubsystemClass).name()] = std::make_unique<SubsystemClass>();
        }

        template<class SubsystemClass>
        SubsystemClass* GetSubsystem()
        {
            return s_subsystems[typeid(SubsystemClass).name()].get();
        }
    private:
        static inline StringHashTable<std::unique_ptr<ISubsystem>> s_subsystems{};

        bool OnCreateSubsystem() override;
        void OnDestroySubsystem() override;
    };
}
