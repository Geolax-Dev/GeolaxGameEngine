#pragma once

#include <Graphics/Utils.h>

namespace GGE
{
    class BgfxProfilerImpl;

    class BgfxProfiler
    {
    public:
        BgfxProfiler();
        ~BgfxProfiler();

        void begin(const char* name, uint32_t abgr, const char* filePath, uint16_t line);
        void end();

    private:
        BgfxProfilerImpl* m_imp{};
    };
}
