#pragma once

#include "Meiosis/Core/Core.hpp"

namespace Meiosis
{
    namespace Renderer
    {
        void init();
        void shutdown();

        void onWindowResize(uint32_t width, uint32_t height);

        void beginScene();
        void endScene();
    }
}