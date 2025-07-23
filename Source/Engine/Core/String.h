#pragma once

#include <Core/Primitives.h>

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <SIMD_String/SIMDString.h>
GUARD_EXTERNAL_INCLUDE_END

namespace GGE
{
    using String = SIMDString<>;
    using SmallString = SIMDString<16>;

    using StringView = std::string_view;
}
