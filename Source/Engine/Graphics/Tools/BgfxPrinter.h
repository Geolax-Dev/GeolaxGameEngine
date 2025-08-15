#pragma once

#include <Graphics/Utils.h>

namespace GGE
{
    class BgfxPrinter
    {
    public:
        BgfxPrinter() = default;
        ~BgfxPrinter() = default;

        void Fatal(const char* pMsg, const char* pErrorCode, const char* pFilePath, uint16_t uLine);
        void Log(const char* pMsg, const char* pFilePath, uint16_t uLine);
    private:
        std::mutex m_logMtx{};
    };
}
