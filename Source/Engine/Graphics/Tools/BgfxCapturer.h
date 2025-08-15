#pragma once

#include <Graphics/Utils.h>

namespace GGE
{
    class BgfxCapturer
    {
    public:
        BgfxCapturer() = default;
        ~BgfxCapturer() = default;

        void beginVideoCapture(uint32_t _width, uint32_t _height, uint32_t _pitch, bgfx::TextureFormat::Enum _format, bool _yflip);
        void endVideoCapture();
        void pushVideoCaptureFrame(const void* _data, uint32_t _size);

        void makeScreenshot(const char* filePath, uint32_t width, uint32_t height, uint32_t pitch, const void* data, uint32_t size, bool yflip);
    };
}
