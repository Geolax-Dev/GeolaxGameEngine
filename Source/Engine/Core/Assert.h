#pragma once

#include <Core/Primitives.h>

#define GGE_ASSERT(...) GGE_ASSERT_HELPER(__VA_ARGS__)

#if DISTRIBUTION_READY
#define GGE_ASSERT_HELPER(expr) expr
#else
#define GGE_ASSERT_HELPER(expr) if (static_cast<bool>(expr) == false) ::GGE::Assert(#expr, __FILE__, __LINE__)
#endif

namespace GGE
{
    void Assert(const char* expr, const char* source, int sourceLine);
}
