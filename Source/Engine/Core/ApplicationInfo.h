#pragma once

#include <Core/Minimal.h>
#include <Core/BuildInfo.h>

namespace GGE
{
    namespace IO
    {
        struct RawResource; // Fwd
    }

    struct ApplicationInfo
    {
        BuildInfo buildInfo = GetBuildInfo(); // Build information
        SmallString applicationName{}; // Name of the application
        SmallString applicationVersion{}; // Version of the application
        String applicationDescription{}; // Description of the application
        SmallString applicationAuthor{}; // Author of the application
        String applicationLicense{}; // License of the application
        SmallString applicationWebsite{}; // Website of the application
        SmallString applicationSupportEmail{}; // Support email for the application
        SmallString applicationSupportPhone{}; // Support phone number for the application
        SmallString applicationSupportAddress{}; // Support address for the application
        SmallString applicationCopyright{}; // Copyright information for the application
        String applicationPath{}; // Path to the application executable

        ApplicationInfo() = default;

        void SaveToRawResource(IO::RawResource& resource) const;

        static ApplicationInfo Create(const StringView& appName, const StringView& appVersion, const StringView& appDescription,
            const StringView& appAuthor, const StringView& appLicense, const StringView& appWebsite,
            const StringView& appSupportEmail, const StringView& appSupportPhone, const StringView& appSupportAddress,
            const StringView& appCopyright, const StringView& appPath)
        {
            ApplicationInfo info;
            info.applicationName = appName;
            info.applicationVersion = appVersion;
            info.applicationDescription = appDescription;
            info.applicationAuthor = appAuthor;
            info.applicationLicense = appLicense;
            info.applicationWebsite = appWebsite;
            info.applicationSupportEmail = appSupportEmail;
            info.applicationSupportPhone = appSupportPhone;
            info.applicationSupportAddress = appSupportAddress;
            info.applicationCopyright = appCopyright;
            info.applicationPath = appPath;
            return info;
        }

        static ApplicationInfo CreateFromRawResource(const IO::RawResource& resource);

        static ApplicationInfo GetDefault();
        static ApplicationInfo GetCurrent();
        static void SetCurrent(const ApplicationInfo& appInfo);

        [[nodiscard]] inline String GetFullVersion() const
        {
            return applicationName + " " + applicationVersion;
        }
    };
}
