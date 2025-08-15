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

        template<class...Args>
        [[maybe_unused]] static inline void Create(Args&&...args) {
            GGE_ASSERT(!s_instance && "Singleton double creation!");

            s_instance = new T(std::forward<Args>(args)...);
        }

        [[maybe_unused]] static inline void Destroy() {
            GGE_ASSERT(s_instance && "Destroy of non-initialized Singleton!");
            delete s_instance;
        }

    private:
        static inline T* s_instance{};

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;
    };
}
