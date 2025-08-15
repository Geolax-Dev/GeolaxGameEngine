#include "BgfxProfiler.h"

#if (DISTRIBUTION_READY == 0)
#define TRACY_ENABLE
#endif // !TRACY_ENABLE

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <tracy/TracyC.h>
GUARD_EXTERNAL_INCLUDE_END

#include <stack>

namespace GGE
{
    class BgfxProfilerImpl
    {
    public:
        BgfxProfilerImpl() = default;
        ~BgfxProfilerImpl() = default;

        std::stack<TracyCZoneCtx>& getStack() { return m_threadLocalContextStack; }
    private:
        static thread_local inline std::stack<TracyCZoneCtx> m_threadLocalContextStack{};
    };

    static constexpr uint32_t AbgrToRgb(uint32_t abgr) {
        uint8_t a = (abgr >> 24) & 0xff; (void)a;
        uint8_t b = (abgr >> 16) & 0xff;
        uint8_t g = (abgr >> 8) & 0xff;
        uint8_t r = (abgr >> 0) & 0xff;
        return (uint32_t(r) << 16) | (uint32_t(g) << 8) | uint32_t(b);
    }
}

GGE::BgfxProfiler::BgfxProfiler()
{
    m_imp = new BgfxProfilerImpl();
}

GGE::BgfxProfiler::~BgfxProfiler()
{
    delete m_imp;
}

void GGE::BgfxProfiler::begin(const char* name, uint32_t abgr, const char* filePath, uint16_t line)
{
    //auto& ctxStack = m_imp->getStack();

    //static const ___tracy_source_location_data location{
    //    .name = name,
    //    .function = __FUNCTION__,
    //    .file = filePath,
    //    .line = line,
    //    .color = AbgrToRgb(abgr)
    //};

    //ctxStack.push(___tracy_emit_zone_begin(&location, 1));
}

void GGE::BgfxProfiler::end()
{
    //auto& ctxStack = m_imp->getStack();
    //GGE_ASSERT((!ctxStack.empty()) && "Trying to end profiler when there's no begin!");

    //___tracy_emit_zone_end(ctxStack.top());
    //ctxStack.pop();
}
