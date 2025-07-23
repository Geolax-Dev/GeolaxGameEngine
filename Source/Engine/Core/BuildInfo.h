#pragma once

#include <Core/Primitives.h>

namespace GGE
{
    typedef uint32 BuildNumberType;

    /**
    * Carries (Maj.Min.Build) version info.
    */
    struct BuildInfo
    {
        BuildNumberType Major{};
        BuildNumberType Minor{};
        BuildNumberType Build{}; // always unique
    };

    /**
    * Returns current build version of the engine's core library.
    */
    [[nodiscard]]
    BuildInfo GetBuildInfo() noexcept;

}
