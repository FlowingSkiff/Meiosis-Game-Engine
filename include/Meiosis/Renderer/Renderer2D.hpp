#pragma once

#include "Meiosis/Core/Core.hpp"

namespace Meiosis::Renderer2D
{
    void init();
    void shutdown();
    void beginScene();
    void endScene();
    void flush();
}