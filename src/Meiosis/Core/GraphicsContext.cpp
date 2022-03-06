#include "Core/GraphicsContext.hpp"
#include "Platform/OpenGL/OpenGLGraphicsContext.hpp"
namespace Meiosis
{
std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window)
{
    return std::make_unique<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(window));
}
}// namespace Meiosis