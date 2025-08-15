#include "BgfxPrinter.h"

void GGE::BgfxPrinter::Fatal(const char* pMsg, const char* pErrorCode, const char* pFilePath, uint16_t uLine)
{
    std::scoped_lock<std::mutex> lock(m_logMtx);
    GGE_LOG_CRITICAL("{} - {}:{} {}", pErrorCode, pFilePath, uLine, pMsg);
}

void GGE::BgfxPrinter::Log(const char* pMsg, const char* pFilePath, uint16_t uLine)
{
    std::scoped_lock<std::mutex> lock(m_logMtx);
    const auto len = strlen(pMsg);
    *(((char*&)pMsg) + len - 1) = 0;
    GGE_LOG_TRACE("[{}:{}]: {}", strstr(pFilePath, "bgfx"), uLine, pMsg);
}
