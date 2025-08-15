#pragma once

#include <Core/Event/Event.h>

namespace GGE
{
    enum WindowEvents
    {
        WindowEvents_WindowClose = 0,
        WindowEvents_WindowResize,
        WindowEvents_WindowFocus,
        WindowEvents_WindowLostFocus,
        WindowEvents_WindowMaximized,
        WindowEvents_WindowMinimized,
        WindowEvents_WindowRestored,
        WindowEvents_WindowMoved,
    };

    struct WindowResizeEvent : public WindowEvent
    {
        EVENT_TYPE(WindowEvents_WindowResize)

        uint32 width;
        uint32 height;

        WindowResizeEvent(uint32 w, uint32 h)
            : width(w), height(h) { }
    };

    SIMPLE_EVENT_DEFINE(WindowEvent, WindowClose);

    SIMPLE_EVENT_DEFINE(WindowEvent, WindowFocus);
    
    SIMPLE_EVENT_DEFINE(WindowEvent, WindowLostFocus);
    
    SIMPLE_EVENT_DEFINE(WindowEvent, WindowMaximized);
    
    SIMPLE_EVENT_DEFINE(WindowEvent, WindowMinimized);
    
    SIMPLE_EVENT_DEFINE(WindowEvent, WindowRestored);
    
    struct WindowMovedEvent : public WindowEvent
    {
        EVENT_TYPE(WindowEvents_WindowMoved);
        
        int x;
        int y;

        WindowMovedEvent(int posX, int posY)
            : x(posX), y(posY) { }
    };
}
