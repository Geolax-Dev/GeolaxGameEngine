#pragma once

#include <Core/Minimal.h>
#include <Core/Singleton.h>
#include <Core/IO/LRUCache.h>
#include <Core/HashTable.h>

#include <filesystem>
#include <memory>
#include <vector>
#include <concepts>
#include <mutex>
#include <shared_mutex>
#include <fstream>
#include <future>
#include <optional>
#include <list>
#include <chrono>

namespace GGE::IO
{
    using std::byte;

    struct RawResource
    {
        std::vector<byte> data{};

        bool empty() const
        {
            return data.empty();
        }

        operator bool() const
        {
            return !data.empty();
        }
    };

    class IFileSystemProvider
    {
    public:
        virtual ~IFileSystemProvider() = default;

        virtual String GetMountPoint() const = 0; // e.g. "assets/"
        virtual bool Exists(const StringView& path) const = 0;
        virtual std::unique_ptr<std::istream> OpenRead(const StringView& localPath) const = 0;
        virtual std::unique_ptr<std::ostream> OpenWrite(const StringView& localPath) const = 0;
        virtual std::vector<String> List(const StringView& localPath) const = 0;
        virtual void Move(const StringView& oldVirtualPath, const StringView& newVirtualPath) const = 0;
        virtual size_t GetSize(const StringView& virtualPath) const = 0;
    };

    class FileResourceManager final : public Singleton<FileResourceManager>
    {
    public:
        FileResourceManager();
        ~FileResourceManager() override;
        FileResourceManager(const FileResourceManager&) = delete;
        FileResourceManager(FileResourceManager&&) = delete;
        FileResourceManager& operator=(const FileResourceManager&) = delete;
        FileResourceManager& operator=(FileResourceManager&&) = delete;

        void RegisterFileSystemProvider(std::shared_ptr<IFileSystemProvider> provider)
        {
            if (!provider) return;
            std::unique_lock wl(m_mutex);
            m_fileSystemProviders[provider->GetMountPoint()] = std::move(provider);
            m_resolveCache.clear(); // Invalidate cache
        }

        RawResource LoadSync(const StringView& virtualPath) const
        {
            const auto normalizedPath = NormalizePath(virtualPath);

            if (auto cached = m_cache->Get(normalizedPath))
                return *cached;

            RawResource resource = LoadResourceRaw(normalizedPath);
            if (!resource.data.empty())
                m_cache->Put(normalizedPath, resource, resource.data.size());

            return resource;
        }

        void PreloadResources(const std::vector<StringView>& virtualPaths)
        {
            std::vector<std::future<void>> futures;
            for (const auto& path : virtualPaths)
            {
                futures.emplace_back(std::async(std::launch::async, [this, path]() {
                    const auto normalizedPath = NormalizePath(path);
                    LoadSync(normalizedPath);
                }));
            }
            for (auto& future : futures) future.get();
        }

        bool Unload(const StringView& virtualPath)
        {
            return m_cache->Remove(NormalizePath(virtualPath));
        }

        void ClearCache()
        {
            m_cache->Clear();
        }

        void SetCacheSize(size_t sizeBytes)
        {
            m_cache->SetMaxSize(sizeBytes);
        }

        size_t CacheVirtualTree(const StringView& virtualPath) const
        {
            size_t totalCached = 0;

            for (const auto& [_, provider] : m_fileSystemProviders)
            {
                totalCached += CacheVirtualTreeRecursively(provider, virtualPath);
            }

            return totalCached;
        }

        std::unique_ptr<std::istream> OpenRead(const StringView& virtualPath) const
        {
            auto& [provider, localPath] = ResolvePath(virtualPath);
            if (!provider) return nullptr;
            return provider->OpenRead(localPath);
        }

        std::unique_ptr<std::ostream> OpenWrite(const StringView& virtualPath) const
        {
            auto& [provider, localPath] = ResolvePath(virtualPath);
            if (!provider) return nullptr;
            return provider->OpenWrite(localPath);
        }

        void Move(const StringView& oldVirtualPath, const StringView& newVirtualPath) const
        {
            auto& [provider, localPath] = ResolvePath(oldVirtualPath);
            if (provider && provider->Exists(localPath))
                provider->Move(localPath, ResolvePath(newVirtualPath).second);
        }

        bool Exists(const StringView& virtualPath) const
        {
            auto& [provider, localPath] = ResolvePath(virtualPath);
            return provider && provider->Exists(localPath);
        }

        size_t GetSize(const StringView& virtualPath) const
        {
            auto& [provider, localPath] = ResolvePath(virtualPath);
            return provider ? provider->GetSize(localPath) : 0u;
        }

        String GetExecutablePath() const;

        String GetExecutableDirectory() const;

    private:
        mutable std::shared_mutex m_mutex{};
        StringHashTable<std::shared_ptr<IFileSystemProvider>> m_fileSystemProviders{};
        mutable StringHashTable<std::pair<std::shared_ptr<IFileSystemProvider>, String>> m_resolveCache{};
        LRUCache<String, RawResource>* m_cache{};

        std::pair<std::shared_ptr<IFileSystemProvider>, String>& ResolvePath(const StringView& virtualPath) const;
        RawResource LoadResourceRaw(const StringView& virtualPath) const;
        size_t CacheVirtualTreeRecursively(const std::shared_ptr<IFileSystemProvider>& provider,
                                         const StringView& localPath) const
        {
            if (!provider) return 0;

            if (localPath.empty() || !provider->Exists(localPath))
                return 0;

            auto files = provider->List(localPath);
            size_t totalCached = files.size();
            for (const auto& file : files)
            {
                const String fullPath = NormalizePath(localPath.empty() ? file : localPath.std_string() + "/" + file.std_string());
                m_resolveCache[fullPath] = { provider, fullPath };
                // Recursively cache subdirectories
                totalCached += CacheVirtualTreeRecursively(provider, fullPath);
            }

            return totalCached;
        }

        static inline String NormalizePath(const StringView& path)
        {
            // Normalize the path by removing redundant slashes and resolving relative paths
            std::filesystem::path fsPath(path.data());
            return fsPath.lexically_normal().string();
        }
    };

}
