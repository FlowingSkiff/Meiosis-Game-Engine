#include "Meiosis/Renderer/Renderer.hpp"
#include "Meiosis/Renderer/RendererAPI.hpp"

namespace Meiosis::Renderer
{
    void init()
    {
        RendererAPI::init();
    }
    void Shutdown()
    {
    }

    void onWindowResize(uint32_t width, uint32_t height)
    {
        RendererAPI::setViewport(0, 0, width, height);
    }

    void beginScene()
    {

    }

    void endScene()
    {

    }


}