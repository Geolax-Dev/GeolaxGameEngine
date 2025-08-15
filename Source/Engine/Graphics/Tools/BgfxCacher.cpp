#include "BgfxCacher.h"

#include <Core/IO/FileResourceManager.h>

namespace GGE
{
    static String defaultCacheRoot()
    {
        // You can tweak this: env var GGE_BGFX_CACHE, else "bgfx_cache"
#if defined(_WIN32)
        char buf[512];
        size_t n = 0;
        if (_dupenv_s((char**)&buf, &n, "GGE_BGFX_CACHE") == 0 && n > 0 && buf) {
            return buf;
        }
#else
        if (const char* env = std::getenv("GGE_BGFX_CACHE")) {
            return env;
        }
#endif

        return "Cache/Renderer";
    }

    BgfxCacher::BgfxCacher()
        : m_root( defaultCacheRoot() )
    {
    }

    BgfxCacher::~BgfxCacher()
    {
    }

    uint32_t BgfxCacher::GetSize(uint64_t _id)
    {
        const auto path = GetPathFor(_id);

        std::lock_guard<std::mutex> lg(m_mutex);
        return (uint32)IO::FileResourceManager::Get().GetSize(path);
    }

    bool BgfxCacher::Get(uint64_t _id, void* _data, uint32_t _size)
    {
        const auto path = GetPathFor(_id);

        std::lock_guard<std::mutex> lg(m_mutex);
        if (auto stream = IO::FileResourceManager::Get().OpenRead(path))
        {
            stream->read((char*)_data, _size);
            return stream->good() && (stream->gcount() == _size);
        }

        return false;
    }

    void BgfxCacher::Set(uint64_t _id, const void* _data, uint32_t _size)
    {
        auto path = GetPathFor(_id);
        const auto tmpPath = path + ".tmp";
        if (auto stream = IO::FileResourceManager::Get().OpenWrite(tmpPath))
        {
            stream->write((const char*)_data, _size);
        }

        IO::FileResourceManager::Get().Move(tmpPath, path);
    }

    String BgfxCacher::GetPathFor(uint64_t id) const
    {
        return String(m_root).append("/").append(GetRendererName()).append(String::hex(id)).append(".bin");
    }


}
