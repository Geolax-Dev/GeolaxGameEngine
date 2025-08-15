#pragma once

#include <Core/Math/VectorMath.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

namespace GGE
{
    static inline String GetRendererName()
    {
        return bgfx::getRendererName(
            bgfx::getRendererType()
        );
    }
}
