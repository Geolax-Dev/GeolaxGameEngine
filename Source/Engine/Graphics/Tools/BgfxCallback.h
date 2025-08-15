#pragma once

#include <Graphics/Utils.h>

namespace GGE
{
    class BgfxPrinter;
    class BgfxProfiler;
    class BgfxCacher;
    class BgfxCapturer;

    class BgfxCallback final : public bgfx::CallbackI
    {
        using OnScreenShotCallback = std::function<void(const char* filePath, uint32_t width, uint32_t height, uint32_t pitch, const void* data, uint32_t size, bool yflip)>;
    public:
        BgfxCallback();
        ~BgfxCallback();

        BgfxCallback(BgfxCallback&&) = delete;

        void fatal(const char* filePath, uint16_t line, bgfx::Fatal::Enum code, const char* str) override;
        void traceVargs(const char* filePath, uint16_t line, const char* format, va_list argList) override;

        void profilerBegin(const char* name, uint32_t abgr, const char* filePath, uint16_t line) override;
        void profilerBeginLiteral(const char* name, uint32_t abgr, const char* filePath, uint16_t line) override;
        void profilerEnd() override;

        uint32_t cacheReadSize(uint64_t _id) override;
        bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override;
        void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override;

        void screenShot(const char* filePath, uint32_t width, uint32_t height, uint32_t pitch, const void* data, uint32_t size, bool yflip) override;
        void OnScreenShot(OnScreenShotCallback callback)
        {
            m_screenShotCb = callback;
        }

        void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx::TextureFormat::Enum _format, bool _yflip) override;
        void captureEnd() override;
        void captureFrame(const void* _data, uint32_t _size) override;

    private:
        BgfxPrinter* m_printer{};
        BgfxProfiler* m_profiler{};
        BgfxCacher* m_cacher{};
        BgfxCapturer* m_capturer{};

        OnScreenShotCallback m_screenShotCb{};
    };
}
