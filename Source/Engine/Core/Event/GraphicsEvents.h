#pragma once

#include <Core/Event/Event.h>

namespace GGE
{
    enum GraphicsEvents
    {
        GraphicsEvents_RenderThreadSpawned,
        GraphicsEvents_RenderThreadInitialized,
        GraphicsEvents_RenderThreadStopped,
    };

    SIMPLE_EVENT_DEFINE(GraphicsEvent, RenderThreadSpawned);

    SIMPLE_EVENT_DEFINE(GraphicsEvent, RenderThreadInitialized);

    SIMPLE_EVENT_DEFINE(GraphicsEvent, RenderThreadStopped);

}
