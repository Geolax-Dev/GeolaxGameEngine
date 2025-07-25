#include "ApplicationInfo.h"

#include <Core/IO/FileResourceManager.h>
#include <Core/Parse/INI.h>

namespace GGE
{
    static ApplicationInfo s_currentAppInfo = ApplicationInfo::GetDefault();

    void ApplicationInfo::SaveToRawResource(IO::RawResource& resource) const
    {
        Parse::INIWriter iniWriter;
        iniWriter.Set("Application", "EngineVersion", std::to_string(buildInfo.Major) + "." + std::to_string(buildInfo.Minor) + "." + std::to_string(buildInfo.Build));
        iniWriter.Set("Application", "Name", applicationName);
        iniWriter.Set("Application", "Version", applicationVersion);
        iniWriter.Set("Application", "Description", applicationDescription);
        iniWriter.Set("Application", "Author", applicationAuthor);
        iniWriter.Set("Application", "License", applicationLicense);
        iniWriter.Set("Application", "Website", applicationWebsite);
        iniWriter.Set("Application", "SupportEmail", applicationSupportEmail);
        iniWriter.Set("Application", "SupportPhone", applicationSupportPhone);
        iniWriter.Set("Application", "SupportAddress", applicationSupportAddress);
        iniWriter.Set("Application", "Copyright", applicationCopyright);

        BufferedStringLoader loader(resource.data);
        loader.append(iniWriter.SaveToString());
        loader.finalize();
    }

    ApplicationInfo GGE::ApplicationInfo::CreateFromRawResource(const IO::RawResource& resource)
    {
        ApplicationInfo appInfo;
        Parse::INIReader iniParser(resource);
        appInfo.applicationName = iniParser.Get("Application", "Name", "Unknown Application");
        appInfo.applicationVersion = iniParser.Get("Application", "Version", "0.0.0");
        appInfo.applicationDescription = iniParser.Get("Application", "Description", "");
        appInfo.applicationAuthor = iniParser.Get("Application", "Author", "");
        appInfo.applicationLicense = iniParser.Get("Application", "License", "");
        appInfo.applicationWebsite = iniParser.Get("Application", "Website", "");
        appInfo.applicationSupportEmail = iniParser.Get("Application", "SupportEmail", "");
        appInfo.applicationSupportPhone = iniParser.Get("Application", "SupportPhone", "");
        appInfo.applicationSupportAddress = iniParser.Get("Application", "SupportAddress", "");
        appInfo.applicationCopyright = iniParser.Get("Application", "Copyright", "");

        // Parse the version string
        SmallString versionStr = iniParser.Get("Application", "EngineVersion", "0.0.0");
        
        sscanf_s(versionStr.c_str(), "%d.%d.%d",
               &appInfo.buildInfo.Major,
               &appInfo.buildInfo.Minor,
               &appInfo.buildInfo.Build);

        // rewrite of loading build info, not using sscanf
        // Parse the application path from the file resource manager
        if (appInfo.buildInfo.Major == 0 && appInfo.buildInfo.Minor == 0 && appInfo.buildInfo.Build == 0)
        {
            // If parsing failed, set to default values
            appInfo.buildInfo = GetBuildInfo();
        }

        // Set the application path to the executable path
        appInfo.applicationPath = IO::FileResourceManager::Get().GetExecutablePath();

        return appInfo;
    }

    ApplicationInfo ApplicationInfo::GetDefault()
    {
        return ApplicationInfo::Create(
            /* applicationName: */ "GGE Application",
            /* applicationVersion: */ "1.0.0",
            /* applicationDescription: */ "A GGE application",
            /* applicationAuthor: */ "krovee (krovee.mail@gmail.com)",
            /* applicationLicense: */ "Proprietary License",
            /* applicationWebsite: */ "",
            /* applicationSupportEmail: */ "",
            /* applicationSupportPhone: */ "",
            /* applicationSupportAddress: */ "",
            /* applicationCopyright: */ "Copyright (c) 2025 krovee (krovee.mail@gmail.com)",
            /* applicationPath: */ IO::FileResourceManager::Get().GetExecutablePath()
        );
    }

    ApplicationInfo ApplicationInfo::GetCurrent()
    {
        return s_currentAppInfo;
    }

    void ApplicationInfo::SetCurrent(const ApplicationInfo& appInfo)
    {
        s_currentAppInfo = appInfo;
    }

}

