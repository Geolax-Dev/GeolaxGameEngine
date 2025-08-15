#pragma once

#include <Core/Primitives.h>

#include <Core/String.h>

GUARD_EXTERNAL_INCLUDE_BEGIN
#include <spdlog/spdlog.h>
GUARD_EXTERNAL_INCLUDE_END

#if !DISTRIBUTION_READY

// define a formatter with GGE::BaseSimdString<> and GGE::StringView
namespace std
{
    // define for GGE::BaseSimdString<INTERNAL_SIZE, Allocator>
    template<size_t INTERNAL_SIZE, class Allocator>
    struct formatter<GGE::BaseSimdString<INTERNAL_SIZE, Allocator>> : formatter<std::string>
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

#define GGE_LOG_TRACE(...) (void)0
#define GGE_LOG_DEBUG(...) (void)0
#define GGE_LOG_INFO(...) (void)0
#define GGE_LOG_WARN(...) (void)0
#define GGE_LOG_ERROR(...) (void)0
#define GGE_LOG_CRITICAL(...) (void)0

#endif // !DISTRIBUTION_READY
