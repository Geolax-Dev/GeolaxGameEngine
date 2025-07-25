#include "Terminal.h"

#ifdef _WIN32

#include <iostream>
#include <vector>
#include <mutex>

#include <windows.h>
#include <Core/BuildInfo.h>

static bool s_enabled = false;

#if !DISTRIBUTION_READY
static HANDLE s_hConsole = INVALID_HANDLE_VALUE;
static std::vector<char> s_buffer;
static const size_t s_bufferSize = 4096;
static std::mutex s_mutex;
static bool is_debuggerPresent = IsDebuggerPresent();
#endif

// Flush internal buffer to the console.
static inline void FlushBuffer() {
#if !DISTRIBUTION_READY
    if (s_buffer.empty() || s_hConsole == INVALID_HANDLE_VALUE)
        return;
    DWORD written = 0;
    WriteConsoleA(s_hConsole, s_buffer.data(), static_cast<DWORD>(s_buffer.size()), &written, nullptr);
    
    if (is_debuggerPresent)
    {
        s_buffer[s_buffer.size()] = 0;
        OutputDebugString(s_buffer.data());
    }

    s_buffer.clear();
#endif
}

void GGE::Debug::EnableTerminal()
{
#if !DISTRIBUTION_READY
    std::lock_guard<std::mutex> lock(s_mutex);
    if (s_enabled)
        return;

    if (AllocConsole()) {
        // Obtain console handle
        s_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        if (GetConsoleMode(s_hConsole, &mode)) {
            // Enable ANSI escape sequences
            SetConsoleMode(s_hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }

        // std::cout, std::clog, std::cerr, std::cin
        FILE* fDummy;
        freopen_s(&fDummy, "CONOUT$", "w", stdout);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        std::cout.clear();
        std::clog.clear();
        std::cerr.clear();
        std::cin.clear();

        // std::wcout, std::wclog, std::wcerr, std::wcin
        HANDLE hConOut = CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        HANDLE hConIn = CreateFile("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
        SetStdHandle(STD_ERROR_HANDLE, hConOut);
        SetStdHandle(STD_INPUT_HANDLE, hConIn);
        std::wcout.clear();
        std::wclog.clear();
        std::wcerr.clear();
        std::wcin.clear();

        const BuildInfo bi = GetBuildInfo();
        std::cout << "Starting GGE Engine v" << bi.Major << "." << bi.Minor << " [build " << bi.Build << "]\n";

        s_enabled = true;
    }
#endif
}

void GGE::Debug::DisableTerminal()
{
#if !DISTRIBUTION_READY
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_enabled)
        return;

    // Flush any remaining output
    FlushBuffer();
    FreeConsole();
    s_enabled = false;
    s_hConsole = INVALID_HANDLE_VALUE;
#endif
}

bool GGE::Debug::IsTerminalEnabled()
{
    return s_enabled;
}

void GGE::Debug::WriteTerminal(const char* text, size_t length)
{
#if !DISTRIBUTION_READY
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_enabled || length == 0)
        return;

    // Append to buffer
    s_buffer.insert(s_buffer.end(), text, text + length);

    // Check for newline in incoming text
    bool hasNewline = (std::memchr(text, '\n', length) != nullptr);

    // Flush if buffer is full or if we've hit a newline
    if (s_buffer.size() >= s_bufferSize || hasNewline) {
        FlushBuffer();
    }
#endif
}

#endif
