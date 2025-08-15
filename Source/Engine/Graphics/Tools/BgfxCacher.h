#pragma once

#include <Graphics/Utils.h>

namespace GGE
{
    class BgfxCacher
    {
    public:
        BgfxCacher();
        ~BgfxCacher();

        uint32_t GetSize(uint64_t _id);
        bool Get(uint64_t _id, void* _data, uint32_t _size);
        void Set(uint64_t _id, const void* _data, uint32_t _size);
    private:
        String m_root{};
        std::mutex m_mutex{};

        String GetPathFor(uint64_t id) const;
    };
}
