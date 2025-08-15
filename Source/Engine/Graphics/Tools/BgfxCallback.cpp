#include "BgfxCallback.h"

#include "BgfxPrinter.h"
#include "BgfxProfiler.h"
#include "BgfxCapturer.h"
#include "BgfxCacher.h"

#include <stdarg.h>

GGE::BgfxCallback::BgfxCallback()
{
    m_printer = new BgfxPrinter();
    m_profiler = new BgfxProfiler();
    m_capturer = new BgfxCapturer();
    m_cacher = new BgfxCacher();

}

GGE::BgfxCallback::~BgfxCallback()
{
    delete m_printer;
    delete m_profiler;
    delete m_cacher;
    delete m_capturer;
}

static constexpr const char* s_FatalToStr(bgfx::Fatal::Enum f)
{
    switch (f)
    {
        case bgfx::Fatal::Enum::DebugCheck: return "DebugCheck";
        case bgfx::Fatal::Enum::InvalidShader:  return "InvalidShader";
        case bgfx::Fatal::Enum::UnableToInitialize: return "UnableToInitialize";
        case bgfx::Fatal::Enum::UnableToCreateTexture:  return "UnableToCreateTexture";
        case bgfx::Fatal::Enum::DeviceLost: return "DeviceLost";
        case bgfx::Fatal::Enum::Count: break;
    }

    return "";
}

void GGE::BgfxCallback::fatal(const char* filePath, uint16_t line, bgfx::Fatal::Enum code, const char* str)
{
    m_printer->Fatal(str, s_FatalToStr(code), filePath, line);
}

void GGE::BgfxCallback::traceVargs(const char* filePath, uint16_t line, const char* format, va_list ap)
{
    static char traceBuffer[2048]{};

    va_list argListCopy;
    va_copy(argListCopy, ap);
    std::vsnprintf(traceBuffer, std::size(traceBuffer), format, argListCopy);
    va_end(argListCopy);

    m_printer->Log(traceBuffer, filePath, line);
}

void GGE::BgfxCallback::profilerBegin(const char* name, uint32_t abgr, const char* filePath, uint16_t line)
{
    m_profiler->begin(name, abgr, filePath, line);
}

void GGE::BgfxCallback::profilerBeginLiteral(const char* name, uint32_t abgr, const char* filePath, uint16_t line)
{
    m_profiler->begin(name, abgr, filePath, line);
}

void GGE::BgfxCallback::profilerEnd()
{
    m_profiler->end();
}

uint32_t GGE::BgfxCallback::cacheReadSize(uint64_t _id)
{
    return m_cacher->GetSize(_id);
}

bool GGE::BgfxCallback::cacheRead(uint64_t _id, void* _data, uint32_t _size)
{
    return m_cacher->Get(_id, _data, _size);
}

void GGE::BgfxCallback::cacheWrite(uint64_t _id, const void* _data, uint32_t _size)
{
    m_cacher->Set(_id, _data, _size);
}

void GGE::BgfxCallback::screenShot(const char* filePath, uint32_t width, uint32_t height, uint32_t pitch, const void* data, uint32_t size, bool yflip)
{
    if (m_screenShotCb)
        m_screenShotCb(filePath, width, height, pitch, data, size, yflip);

    m_capturer->makeScreenshot(filePath, width, height, pitch, data, size, yflip);
}

void GGE::BgfxCallback::captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx::TextureFormat::Enum _format, bool _yflip)
{
    m_capturer->beginVideoCapture(_width, _height, _pitch, _format, _yflip);
}

void GGE::BgfxCallback::captureEnd()
{
    m_capturer->endVideoCapture();
}

void GGE::BgfxCallback::captureFrame(const void* _data, uint32_t _size)
{
    m_capturer->pushVideoCaptureFrame(_data, _size);
}
