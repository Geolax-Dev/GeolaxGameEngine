#include "Assert.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <stacktrace>
#include <optional>

GUARD_EXTERNAL_INCLUDE_BEGIN
#ifdef _WIN32
#include <windows.h>
#include <debugapi.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#else
#include <unistd.h>
#endif
GUARD_EXTERNAL_INCLUDE_END

namespace Internal
{
    bool IsConsolePresent();
    void ShowGuiMessageBox(const std::string& message);
    std::string GetStackTrace();
    std::wstring StringToWide(const std::string& multibyte);
}

void GGE::Assert(const char* expr, const char* source, int sourceLine)
{
    std::string message;
    message += "Assertion Failed!\n";
    message += "Expression: " + std::string(expr) + "\n";
    message += "File: " + std::string(source) + "\n";
    message += "Line: " + std::to_string(sourceLine) + "\n\n";
    message += "Stack Trace:\n" + Internal::GetStackTrace();

    // Try printing to console first (if available)
    if (Internal::IsConsolePresent()) {
        std::fprintf(stderr, "%s", message.c_str());
        std::fflush(stderr);
    }
    else {
        // Fallback to GUI message box
        Internal::ShowGuiMessageBox(message);
    }

    std::abort(); // Terminate program
}

bool Internal::IsConsolePresent()
{
#ifdef _WIN32
    return GetConsoleWindow() != nullptr;
#else
    return isatty(STDERR_FILENO);
#endif
}

void Internal::ShowGuiMessageBox(const std::string& message)
{
#ifdef _WIN32
    MessageBoxA(nullptr, message.c_str(), "Assertion Failed", MB_ICONERROR | MB_OK);
#elif defined(__APPLE__)
    // macOS uses Objective-C, but we can use a simple `osascript` call
    std::string script = "osascript -e 'tell app \"System Events\" to display dialog \"" +
        message + "\" with icon stop buttons {\"OK\"}'";
    std::system(script.c_str());
#else
    // Linux: Try Zenity, KDialog, or fallback to terminal
    if (std::system("which zenity > /dev/null 2>&1") == 0) {
        std::string cmd = "zenity --error --text=\"" + message + "\" --title=\"Assertion Failed\"";
        std::system(cmd.c_str());
    }
    else if (std::system("which kdialog > /dev/null 2>&1") == 0) {
        std::string cmd = "kdialog --title \"Assertion Failed\" --error \"" + message + "\"";
        std::system(cmd.c_str());
    }
    else {
        // Last resort: Try printing to stderr anyway
        std::fprintf(stderr, "%s", message.c_str());
    }
#endif
}

static inline std::string shrink_path_to_width(std::string_view path, std::size_t max_width) {
    if (path.length() <= max_width) {
        return std::string(path);
    }

    // We need at least 5 characters to make a meaningful shrink (a...b)
    if (max_width < 5) {
        return std::string(path.substr(0, max_width));
    }

    // Find last separator before the middle
    const auto last_sep_before = path.find_last_of(R"(/\)", max_width / 2);

    // Find first separator after the middle
    const auto first_sep_after = path.find_first_of(R"(/\)", path.length() - (max_width / 2));

    // Calculate positions for the split
    const auto left_part = (last_sep_before != std::string_view::npos)
        ? path.substr(0, last_sep_before + 1)
        : path.substr(0, max_width / 2);

    const auto right_part = (first_sep_after != std::string_view::npos)
        ? path.substr(first_sep_after)
        : path.substr(path.length() - (max_width / 2));

    // If the combined parts with "..." fit, use them
    if (left_part.length() + right_part.length() + 3 <= max_width) {
        return std::string(left_part) + "..." + std::string(right_part);
    }

    // If not, just truncate with ellipsis at the end
    return std::string(path.substr(0, max_width - 3)) + "...";
}

std::string Internal::GetStackTrace()
{
    const auto trace = std::stacktrace::current(2);
    std::string result = "";

    for (const auto& entry : trace) {
        const auto fn = entry.description();
        const auto loc = entry.source_file();

        result += "  at " + fn + "\n";

        if (loc.size())
        {
            result += "    in " + shrink_path_to_width(loc, 48) +
                ":" + std::to_string(entry.source_line()) + "\n";
        }
    }

    return result;
}

std::wstring Internal::StringToWide(const std::string& multibyte)
{
#if defined(_WIN32)
    if (multibyte.empty()) return L"";

    int size = MultiByteToWideChar(
        CP_UTF8, 0,
        multibyte.data(), static_cast<int>(multibyte.size()),
        nullptr, 0
    );

    std::wstring result((size_t)size, L'\0');
    MultiByteToWideChar(
        CP_UTF8, 0,
        multibyte.data(), static_cast<int>(multibyte.size()),
        result.data(), size
    );

    return result;
#endif 
}
