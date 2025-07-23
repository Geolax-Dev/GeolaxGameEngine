#pragma once

#include <Core/HID/HIDBase.h>

namespace GGE::HID
{
    // Keyboard keys enumeration (reflects the GLFW key codes)
    enum class KeyboardKey : ElementType
    {
        eUnknown = 0,
        eSpace = 32,
        eApostrophe = 39, // '
        eComma = 44, // ,
        eMinus = 45, // -
        ePeriod = 46, // .
        eSlash = 47, // /
        eNum0 = 48,
        eNum1 = 49,
        eNum2 = 50,
        eNum3 = 51,
        eNum4 = 52,
        eNum5 = 53,
        eNum6 = 54,
        eNum7 = 55,
        eNum8 = 56,
        eNum9 = 57,
        eSemicolon = 59, // ;
        eEqual = 61, // =
        eA = 65,
        eB = 66,
        eC = 67,
        eD = 68,
        eE = 69,
        eF = 70,
        eG = 71,
        eH = 72,
        eI = 73,
        eJ = 74,
        eK = 75,
        eL = 76,
        eM = 77,
        eN = 78,
        eO = 79,
        eP = 80,
        eQ = 81,
        eR = 82,
        eS = 83,
        eT = 84,
        eU = 85,
        eV = 86,
        eW = 87,
        eX = 88,
        eY = 89,
        eZ = 90,
        eLeftBracket = 91, // [
        eBackslash = 92, // '\'
        eRightBracket = 93, // ]
        
        eGraveAccent = 96, // `
        
        eWorld1 = 161, // non-US #1
        eWorld2, // non-US #2
        eEscape = 256,
        eEnter = 257,
        eTab = 258,
        eBackspace = 259,
        eInsert = 260,
        eDelete = 261,
        eRight = 262,
        eLeft = 263,
        eDown = 264,
        eUp = 265,
        ePageUp = 266,
        ePageDown = 267,
        eHome = 268,
        eEnd = 269,
        eCapsLock = 280,
        eScrollLock = 281,
        eNumLock = 282,
        ePrintScreen = 283,
        ePause = 284,
        // start F keys
        eF1 = 290,
        eF2 = 291,
        eF3 = 292,
        eF4 = 293,
        eF5 = 294,
        eF6 = 295,
        eF7 = 296,
        eF8 = 297,
        eF9 = 298,
        eF10 = 299,
        eF11 = 300,
        eF12 = 301,
        // end F keys
    };

    // Keyboard device class
    class KeyboardDevice : public IDevice
    {
    public:
        // Check if a key is pressed
        static bool IsKeyPressed(KeyboardKey key);
        // Check if a key was just pressed
        static bool IsKeyJustPressed(KeyboardKey key);
        // Check if a key was just released
        static bool IsKeyJustReleased(KeyboardKey key);
        // Get the name of a key
        static const char* GetKeyName(KeyboardKey key);

        static KeyboardKey GetLastPressedKey();

        [[maybe_unused]] static DeviceKind GetDeviceKind() { return DeviceKind::eKeyboard; }
    };
}
