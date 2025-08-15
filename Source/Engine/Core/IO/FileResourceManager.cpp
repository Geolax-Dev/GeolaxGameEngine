#include "FileResourceManager.h"

#ifdef _WIN32
GUARD_EXTERNAL_INCLUDE_BEGIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
GUARD_EXTERNAL_INCLUDE_END
#endif

namespace GGE::IO
{
    String FileResourceManager::GetExecutablePath() const
    {
        char buffer[MAX_PATH];
#ifdef _WIN32
        if (GetModuleFileNameA(GetModuleHandle(NULL), buffer, MAX_PATH) == 0)
            return {};
#endif
        return buffer;
    }

    String FileResourceManager::GetExecutableDirectory() const
    {
        String path = GetExecutablePath();
        if (path.empty())
            return {};

        // Remove the executable name from the path
        auto pos = path.find_last_of("/\\");
        if (pos != String::npos)
            path.erase(pos + 1); // Keep the trailing slash
        
        return path;
    }

    FileResourceManager::FileResourceManager() 
        : m_cache(new LRUCache<String, RawResource>(1024ull * 1024ull * 10024ull)) // 1G cache
    {
    }
    FileResourceManager::~FileResourceManager()
    {
        if (m_cache)
        {
            m_cache->Clear();
            delete m_cache;
            m_cache = nullptr;
        }
    }
    std::pair<std::shared_ptr<IFileSystemProvider>, String>& GGE::IO::FileResourceManager::ResolvePath(const StringView& unvirtualPath) const
    {
        static std::pair<std::shared_ptr<IFileSystemProvider>, String> emptyPair{ nullptr, {} };

        const auto virtualPath = NormalizePath(unvirtualPath);

        { 
            std::shared_lock rl(m_mutex);
            if (auto it = m_resolveCache.find(virtualPath); it != m_resolveCache.end())
            return it->second;
        }

        // split mount
        auto pos = virtualPath.find('/');
        const String mount = pos == String::npos
                              ? virtualPath
                              : virtualPath.substr(0, pos+1);

        //std::shared_ptr<IFileSystemProvider> prov;

        //{ 
        //    std::shared_lock rl(m_mutex);
        //    for (auto& [_, provider] : m_fileSystemProviders)
        //    {
        //        if (provider->GetMountPoint() == mount)
        //        {
        //            prov = provider;
        //            break;
        //        }
        //    }

        //    //auto pit = m_fileSystemProviders.find( mount);
        //    //if (pit != m_fileSystemProviders.end()) 
        //    //    prov = pit->second;
        //}
        //
        //if (!prov) 
        //    return emptyPair;

        //const StringView local = virtualPath.substr(mount.size());

        //if (!prov->Exists(local)) 
        //    return emptyPair;

        // we're providing a local path so, we first need to find the provider 
        // that have directory or file with that name just by iterating through all providers
        std::shared_ptr<IFileSystemProvider> prov;
        {
            std::shared_lock rl(m_mutex);

            for (const auto& [_, provider] : m_fileSystemProviders)
            {
                if (provider->Exists(virtualPath))
                {
                    prov = provider;
                    break;
                }
            }
        }

        { 
            std::unique_lock wl(m_mutex);
            m_resolveCache[virtualPath] = { prov, virtualPath };
        }

        return m_resolveCache[virtualPath];
    }

    RawResource FileResourceManager::LoadResourceRaw(const StringView& virtualPath) const
    {
        auto& [prov, p] = ResolvePath(virtualPath);
        if (!prov)
            return {};

        auto stream = prov->OpenRead(p);

        stream->seekg(0, std::ios::end);
        const std::streamoff sz = stream->tellg();
        stream->seekg(0);

        RawResource r; 
        r.data.resize(static_cast<size_t>(sz));

        stream->read(reinterpret_cast<char*>(r.data.data()), sz);

        return r;
    }
}

