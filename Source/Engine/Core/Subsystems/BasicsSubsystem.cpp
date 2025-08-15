#include "BasicsSubsystem.h"

#include <Core/Debug/Terminal.h>
#include <Core/IO/RealFileSystemProvider.h>

#include <Core/Logging.h>

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async_logger.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
GUARD_EXTERNAL_INCLUDE_END

namespace GGE
{
    std::shared_ptr<spdlog::logger> g_spdlog_logger;
}

bool GGE::BasicsSubsystem::OnCreateSubsystem()
{
    Debug::EnableTerminal();

#if !DISTRIBUTION_READY
    GGE_ASSERT(SetupSpdlog() && "Failed to setup spdlog!");
#endif

    IO::FileResourceManager::Create();
    IO::FileResourceManager::Get().RegisterFileSystemProvider(
        std::make_shared<IO::RealFileSystemProvider>(
            IO::FileResourceManager::Get().GetExecutableDirectory()
        )
    );

    if constexpr (!DISTRIBUTION_READY)
    {
        const auto cachedCount = IO::FileResourceManager::Get().CacheVirtualTree(".");
        GGE_LOG_INFO("Cached {} resources in the virtual tree '.'", cachedCount);
    }

    GGE_LOG_INFO("BasicsSubsystem created successfully.");
    return true;
}

void GGE::BasicsSubsystem::OnDestroySubsystem()
{
    IO::FileResourceManager::Destroy();

#if !DISTRIBUTION_READY
    ShutdownSpdlog();
#endif

    Debug::DisableTerminal();
}

bool GGE::BasicsSubsystem::SetupSpdlog()
{
    // setup spdlog to use async logger 
    spdlog::init_thread_pool(8192, 2); // queue with 8k items and 2 backing threads.

    // create a logger that logs to both console and file with multiple sinks
    g_spdlog_logger = std::make_shared<spdlog::logger>(
        "spdlog_logger",
        spdlog::sinks_init_list{
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                (IO::FileResourceManager::Get().GetExecutablePath() + ".log.txt").std_string(), true
            ),
            std::make_shared<spdlog::sinks::msvc_sink_mt>()
        }
    );

    g_spdlog_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] %v");
    g_spdlog_logger->set_level(spdlog::level::trace); // Set the default log level to trace

    g_spdlog_logger->set_error_handler([](const std::string& msg) {
        std::cerr << "Spdlog error: " << msg << std::endl;
    });

    spdlog::set_default_logger(g_spdlog_logger);

    GGE_LOG_TRACE("Spdlog initialized with async file logger.");

    return true;
}

void GGE::BasicsSubsystem::ShutdownSpdlog()
{
}
