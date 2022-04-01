#pragma once
#include "Meiosis/Core/Core.hpp"
#include <glm/glm.hpp>
namespace Meiosis
{
namespace RendererAPI
{
    enum class API {
        None = 0,
        OpenGL
    };

    void init();
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void setClearColor(const glm::vec4& color);
    void clear();
    API getAPI();
}// namespace RendererAPI
}// namespace Meiosis