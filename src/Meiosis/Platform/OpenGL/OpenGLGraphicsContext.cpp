#include "Platform/OpenGL/OpenGLGraphicsContext.hpp"
#include "Core/Log.hpp"
#include <glad/glad.h>
#include <glfw/glfw3.h>
namespace Meiosis
{
OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window) : m_window(window)
{
}

void OpenGLGraphicsContext::init()
{
    glfwMakeContextCurrent(m_window);
    auto status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    if (status)
        ME_ENGINE_ERROR("Could not initialize GLAD");

    ME_ENGINE_INFO("OpenGL Info:");
    ME_ENGINE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
    ME_ENGINE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
    ME_ENGINE_INFO("  Version: {}", glGetString(GL_VERSION));
}

void OpenGLGraphicsContext::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

}// namespace Meiosis