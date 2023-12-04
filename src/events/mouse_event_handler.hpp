#pragma once

#include "../logger.hpp"

namespace nc::events{
    class MouseMoveEventHandler
    {
        public:
            MouseMoveEventHandler(){}
            ~MouseMoveEventHandler(){}
            void mouseMove() 
            {
                NC_LOG_INFO("Mouse move");
            }
    };
}