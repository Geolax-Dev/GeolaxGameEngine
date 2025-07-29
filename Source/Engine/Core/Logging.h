#pragma once

#include <Core/Primitives.h>

#include <Core/String.h>

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <spdlog/spdlog.h>
GUARD_EXTERNAL_INCLUDE_END

#if !DISTRIBUTION_READY

// define a formatter with GGE::BaseSimdString<> and GGE::StringView
namespace spdlog
{
    // define for GGE::BaseSimdString<INTERNAL_SIZE, Allocator>
    template<size_t INTERNAL_SIZE, class Allocator>
    struct std::formatter<GGE::BaseSimdString<INTERNAL_SIZE, Allocator>> : std::formatter<std::string>
    {
        auto format(const GGE::BaseSimdString<INTERNAL_SIZE, Allocator>& my, std::format_context& ctx) const -> decltype(ctx.out())
        {
            return std::format_to(ctx.out(), "{}", my.std_string_view());
        }
    };
}

#define GGE_LOG_TRACE(...) \
    ::spdlog::trace(__VA_ARGS__)

#define GGE_LOG_DEBUG(...) \
    ::spdlog::debug(__VA_ARGS__)

#define GGE_LOG_INFO(...) \
    ::spdlog::info(__VA_ARGS__)

#define GGE_LOG_WARN(...) \
    ::spdlog::warn(__VA_ARGS__)

#define GGE_LOG_ERROR(...) \
    ::spdlog::error(__VA_ARGS__)

#define GGE_LOG_CRITICAL(...) \
    ::spdlog::critical(__VA_ARGS__)

#else

#define GGE_LOG_TRACE(...)
#define GGE_LOG_DEBUG(...)
#define GGE_LOG_INFO(...)
#define GGE_LOG_WARN(...)
#define GGE_LOG_ERROR(...)
#define GGE_LOG_CRITICAL(...)

#endif // !DISTRIBUTION_READY
