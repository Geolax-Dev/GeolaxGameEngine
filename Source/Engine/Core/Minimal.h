#pragma once

#include <Core/Macros/MacroNamespace.h>
#include <Core/Macros/MacroUtils.h>

#include <Core/Primitives.h>
#include <Core/Assert.h>
#include <Core/String.h>
#include <Core/HashTable.h>

namespace GGE
{
    struct DisplayPosition
    {
        int32 x{ 0 };
        int32 y{ 0 };
        [[maybe_unused]] DisplayPosition() = default;
        [[maybe_unused]] DisplayPosition(int32 x, int32 y)
            : x(x), y(y) {}
    };

    struct DisplaySize
    {
        uint32 width{ 0 };
        uint32 height{ 0 };
        [[maybe_unused]] DisplaySize() = default;
        [[maybe_unused]] DisplaySize(uint32 width, uint32 height)
            : width(width), height(height) {}
    };
}
