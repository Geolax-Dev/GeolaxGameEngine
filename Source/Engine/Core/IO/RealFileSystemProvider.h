#pragma once

#include <Core/IO/FileResourceManager.h>

namespace GGE::IO
{
    class RealFileSystemProvider final : public IFileSystemProvider
    {
    public:
        explicit RealFileSystemProvider(const String& mountPoint)
            : m_mountPoint(mountPoint.std_string_view()) {
            GGE_LOG_INFO("RealFileSystemProvider created with mount point: {}", m_mountPoint.string());
        }

        String GetMountPoint() const override
        {
            return m_mountPoint.string();
        }
        bool Exists(const StringView& path) const override
        {
            return std::filesystem::exists(m_mountPoint / path.data());
        }
        std::unique_ptr<std::istream> OpenRead(const StringView& localPath) const override 
        {
            if (localPath.empty() || !Exists(localPath))
                return nullptr;

            const auto fullPath = m_mountPoint / localPath.data();
            return std::make_unique<std::ifstream>(fullPath, std::ios::binary);
        }
        std::unique_ptr<std::ostream> OpenWrite(const StringView& localPath) const override
        {
            if (localPath.empty() || !Exists(localPath))
                return nullptr;

            const auto fullPath = m_mountPoint / localPath.data();
            return std::make_unique<std::ofstream>(fullPath, std::ios::binary);
        }
        std::vector<String> List(const StringView& localPath) const override
        {
            std::vector<String> files;
            auto dirPath = m_mountPoint / localPath.data();
            if (std::filesystem::is_directory(dirPath))
            {
                for (const auto& entry : std::filesystem::directory_iterator(dirPath))
                {
                    files.push_back(entry.path().filename().wstring());
                }
            }
            return files;
        }
    private:
        std::filesystem::path m_mountPoint;
    };
} // namespace GGE::IO
