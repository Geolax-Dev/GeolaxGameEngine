#pragma once

#include <Core/IO/FileResourceManager.h>

#include <unordered_set>

namespace GGE::IO
{
    class RealFileSystemProvider final : public IFileSystemProvider
    {
    public:
        explicit RealFileSystemProvider(const String& mountPoint)
            : m_mountPoint(mountPoint.std_string_view()) {
        }

        RealFileSystemProvider(RealFileSystemProvider&) = delete;
        RealFileSystemProvider(RealFileSystemProvider&&) noexcept = delete;

        [[nodiscard]] String GetMountPoint() const override {
            return m_mountPoint.string();
        }

        [[nodiscard]] bool Exists(const StringView& path) const override {
            const auto p = m_mountPoint / path.data();
            std::error_code ec;
            const bool ok = std::filesystem::exists(p, ec);
            if (ec) GGE_LOG_WARN("Exists('{}') failed: {} ({})", p.string(), ec.message(), ec.value());
            return ok && !ec;
        }

        [[nodiscard]] std::unique_ptr<std::istream> OpenRead(const StringView& localPath) const override {
            if (localPath.empty()) return nullptr;
            const auto fullPath = m_mountPoint / localPath.data();
            auto in = std::make_unique<std::ifstream>(fullPath, std::ios::binary);
            if (!in->is_open()) {
                GGE_LOG_ERROR("OpenRead('{}') failed: cannot open", fullPath.string());
                return nullptr;
            }
            return in;
        }

        [[nodiscard]] std::unique_ptr<std::ostream> OpenWrite(const StringView& localPath) const override {
            if (localPath.empty()) return nullptr;
            const auto fullPath = m_mountPoint / localPath.data();

            // Fast path: only call create_directories once per unique parent dir.
            const auto parent = fullPath.parent_path();
            if (!parent.empty() && !isKnownDir(parent)) {
                std::error_code ec;
                std::filesystem::create_directories(parent, ec);
                if (ec) {
                    GGE_LOG_ERROR("OpenWrite('{}') mkdir failed: {} ({})",
                        parent.string(), ec.message(), ec.value());
                    return nullptr;
                }
                rememberDir(parent);
            }

            auto out = std::make_unique<std::ofstream>(fullPath, std::ios::binary | std::ios::trunc);
            if (!out->is_open()) {
                GGE_LOG_ERROR("OpenWrite('{}') failed: cannot open for write", fullPath.string());
                return nullptr;
            }
            return out;
        }

        [[nodiscard]] std::vector<String> List(const StringView& localPath) const override {
            std::vector<String> files;
            const auto dirPath = m_mountPoint / localPath.data();

            std::error_code ec;
            if (!std::filesystem::is_directory(dirPath, ec)) {
                if (ec) GGE_LOG_WARN("List('{}') is_directory failed: {} ({})",
                    dirPath.string(), ec.message(), ec.value());
                return files;
            }

            std::filesystem::directory_iterator it(
                dirPath,
                std::filesystem::directory_options::skip_permission_denied,
                ec
            );
            if (ec) {
                GGE_LOG_WARN("List('{}') iterator failed: {} ({})",
                    dirPath.string(), ec.message(), ec.value());
                return files;
            }

            // No per-entry stat calls—just collect names.
            for (const auto& entry : it) {
                const auto name = entry.path().filename();
                if (!name.empty()) files.emplace_back(name.wstring());
            }
            return files;
        }

        void Move(const StringView& oldVirtualPath, const StringView& newVirtualPath) const override {
            if (oldVirtualPath.empty() || newVirtualPath.empty()) return;

            const auto from = m_mountPoint / oldVirtualPath.data();
            const auto to = m_mountPoint / newVirtualPath.data();

            std::error_code ec;

            // Ensure destination dir exists (with memoization).
            const auto destDir = to.parent_path();
            if (!destDir.empty() && !isKnownDir(destDir)) {
                std::filesystem::create_directories(destDir, ec);
                if (ec) {
                    GGE_LOG_ERROR("Move('{}' -> '{}') mkdir failed: {} ({})",
                        from.string(), destDir.string(), ec.message(), ec.value());
                    return;
                }
                rememberDir(destDir);
            }

            // 1) Fast path: atomic rename on same device.
            ec.clear();
            std::filesystem::rename(from, to, ec);
            if (!ec) return;

            // 2) Fallback: copy then remove (handles EXDEV and other cases).
            GGE_LOG_WARN("Move('{}' -> '{}') rename failed: {} ({}); using copy+remove",
                from.string(), to.string(), ec.message(), ec.value());

            if (std::filesystem::is_directory(from)) {
                std::filesystem::copy(from, to,
                    std::filesystem::copy_options::recursive |
                    std::filesystem::copy_options::overwrite_existing, ec);
                if (ec) {
                    GGE_LOG_ERROR("Move('{}' -> '{}') copy(dir) failed: {} ({})",
                        from.string(), to.string(), ec.message(), ec.value());
                    return;
                }
                std::filesystem::remove_all(from, ec);
                if (ec) {
                    GGE_LOG_WARN("Move('{}') remove_all failed after copy: {} ({})",
                        from.string(), ec.message(), ec.value());
                }
            }
            else {
                std::filesystem::copy_file(from, to,
                    std::filesystem::copy_options::overwrite_existing, ec);
                if (ec) {
                    GGE_LOG_ERROR("Move('{}' -> '{}') copy(file) failed: {} ({})",
                        from.string(), to.string(), ec.message(), ec.value());
                    return;
                }
                std::filesystem::remove(from, ec);
                if (ec) {
                    GGE_LOG_WARN("Move('{}') remove failed after copy: {} ({})",
                        from.string(), ec.message(), ec.value());
                }
            }
        }

        size_t GetSize(const StringView& virtualPath) const override
        {
            const auto path = m_mountPoint / virtualPath.data();
            std::error_code ec;

            const auto st = std::filesystem::status(path, ec);
            if (ec || !std::filesystem::exists(st) || !std::filesystem::is_regular_file(st))
                return 0;

            const auto sz = std::filesystem::file_size(path, ec);
            if (ec || sz == static_cast<uintmax_t>(-1))
                return 0;

            return sz;
        }

    private:
        // Small memoization of created directories (speeds up repeated writes)
        bool isKnownDir(const std::filesystem::path& p) const {
            std::scoped_lock lk(m_dirsMutex);
            return m_createdDirs.find(p) != m_createdDirs.end();
        }
        void rememberDir(const std::filesystem::path& p) const {
            std::scoped_lock lk(m_dirsMutex);
            m_createdDirs.insert(p);
        }

    private:
        std::filesystem::path m_mountPoint;

        // mutable because we memoize even in const methods (thread-safe)
        mutable std::unordered_set<std::filesystem::path> m_createdDirs;
        mutable std::mutex m_dirsMutex;
    };
} // namespace GGE::IO
