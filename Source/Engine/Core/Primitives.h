#pragma once

#include <Core/Macros/MacroNamespace.h>
#include <Core/Macros/MacroUtils.h>

#include <cstddef>
#include <cstdint>
#include <array>
#include <type_traits>

#define REDEFINE_STD_TYPE_WITHOUT_T(x) \
typedef std::x##_t x

namespace GGE
{
    REDEFINE_STD_TYPE_WITHOUT_T(uint8);
    REDEFINE_STD_TYPE_WITHOUT_T(uint16);
    REDEFINE_STD_TYPE_WITHOUT_T(uint32);
    REDEFINE_STD_TYPE_WITHOUT_T(uint64);
    REDEFINE_STD_TYPE_WITHOUT_T(uintptr);

    REDEFINE_STD_TYPE_WITHOUT_T(int8);
    REDEFINE_STD_TYPE_WITHOUT_T(int16);
    REDEFINE_STD_TYPE_WITHOUT_T(int32);
    REDEFINE_STD_TYPE_WITHOUT_T(int64);
    REDEFINE_STD_TYPE_WITHOUT_T(intptr);
}

#undef REDEFINE_STD_TYPE_WITHOUT_T
