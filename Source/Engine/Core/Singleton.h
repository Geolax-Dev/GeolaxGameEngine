#pragma once

#include <Core/Minimal.h>
#include "Window.h"

namespace GGE
{
    template<class T>
    class Singleton
    {
    public:
        [[maybe_unused]] Singleton() = default;
        [[maybe_unused]] virtual ~Singleton() = default;

        [[maybe_unused]] static inline T& Get() noexcept {
            return *s_instance;
        }

        [[maybe_unused]] static inline T* GetP() noexcept {
            return s_instance;
        }

        [[maybe_unused]] static inline bool Create() {
            GGE_ASSERT(!s_instance && "Singleton double creation!");

            s_instance = new T();
            return s_instance->OnCreate();
        }

        [[maybe_unused]] static inline void Destroy() {
            GGE_ASSERT(s_instance && "Destroy of non-initialized Singleton!");
            s_instance->OnDestroy();
            delete s_instance;
        }

        virtual bool OnCreate() = 0;
        virtual void OnDestroy() {}
    private:
        static inline T* s_instance{};
    };
}
