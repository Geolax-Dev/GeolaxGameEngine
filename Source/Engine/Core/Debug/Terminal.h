#pragma once

#include <Core/Primitives.h>

namespace GGE::Debug
{
    [[maybe_unused]] void EnableTerminal();
    [[maybe_unused]] void DisableTerminal();
    [[maybe_unused]] bool IsTerminalEnabled();
    [[maybe_unused]] void WriteTerminal(const char* text, size_t length);
}
