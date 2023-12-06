#pragma once

#include "../logger.hpp"

namespace nc::events {
    class MouseMoveEventHandler
    {
    public:
        MouseMoveEventHandler() {}
        ~MouseMoveEventHandler() {}
        void mouseMove(float x, float y) { NC_LOG_INFO("Mouse move {}:{}", x, y); }
    };
}