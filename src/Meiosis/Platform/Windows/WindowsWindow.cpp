#include "Platform/Windows/WindowsWindow.hpp"
#include "Core/Log.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "Platform/OpenGL/OpenGLGraphicsContext.hpp"
namespace Meiosis
{
static void GLFWErrorCallback(int error, const char* description)
{
    ME_ENGINE_ERROR("GLFW Error ({}): {}", error, description);
}

static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    data.width = width;
    data.height = height;
    WindowResizeEvent event(width, height);
    data.callback(event);
}

static void GLFWWindowShouldCloseCallback(GLFWwindow* window)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    WindowCloseEvent event;
    data.callback(event);
}

static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    switch (action)
    {
        case GLFW_PRESS:
        {
            KeyPressedEvent event(static_cast<KeyCode>(key), 0);
            data.callback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            KeyReleasedEvent event(static_cast<KeyCode>(key));
            data.callback(event);
            break;
        }
        case GLFW_REPEAT:
        {
            KeyPressedEvent event(static_cast<KeyCode>(key), 1);
            data.callback(event);
            break;
        }
        default:
            ME_ENGINE_ERROR("Could not handle key event, unhandled action type({})", action);
    }
}

static void GLFWCharCallback(GLFWwindow* window, unsigned int keycode)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    KeyTypedEvent event(static_cast<KeyCode>(keycode));
    data.callback(event);
}

static void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    switch (action)
    {
        case GLFW_PRESS:
        {
            MouseButtonPressedEvent event(static_cast<MouseCode>(button));
            data.callback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
            data.callback(event);
            break;
        }
        default:
        {
            ME_ENGINE_ERROR("Uknown mouse button action ({})", action);
            break;
        }
    }
}

static void GLFWScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    MouseScrolledEvent event(static_cast<float>(x_offset), static_cast<float>(y_offset));
    data.callback(event);
}

static void GLFWCursorPosCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    auto& data = *static_cast<WindowsWindow::WindowData*>(glfwGetWindowUserPointer(window));
    MouseMovedEvent event(static_cast<float>(x_pos), static_cast<float>(y_pos));
    data.callback(event);
}

WindowsWindow::WindowsWindow(const std::string& name, uint32_t width, uint32_t height) : m_window(nullptr), m_context(nullptr), m_data{ name, width, height, false, 0 }
{
    ME_ENGINE_INFO("Creating window {} ({}, {})", m_data.title, m_data.width, m_data.height);
    auto init_success = glfwInit();
    if (init_success != GLFW_TRUE)
    {
        ME_ENGINE_ERROR("Failed to initialize GLFW");
    }
    glfwSetErrorCallback(GLFWErrorCallback);
    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    m_context = GraphicsContext::create(m_window);
    m_context->init();
    glfwSetWindowUserPointer(m_window, &m_data);
    setVSync(true);
    glfwSetWindowSizeCallback(m_window, GLFWWindowSizeCallback);
    glfwSetWindowCloseCallback(m_window, GLFWWindowShouldCloseCallback);
    glfwSetKeyCallback(m_window, GLFWKeyCallback);
    glfwSetCharCallback(m_window, GLFWCharCallback);
    glfwSetMouseButtonCallback(m_window, GLFWMouseButtonCallback);
    glfwSetScrollCallback(m_window, GLFWScrollCallback);
    glfwSetCursorPosCallback(m_window, GLFWCursorPosCallback);
}

WindowsWindow::~WindowsWindow()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
void WindowsWindow::onUpdate()
{
    glfwPollEvents();
    m_context->swapBuffers();
}
void WindowsWindow::setVSync(bool enabled)
{
    if (m_data.is_vsync = enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}
bool WindowsWindow::isVSync() const
{
    return m_data.is_vsync;
}
uint32_t WindowsWindow::getWidth() const
{
    return m_data.width;
}
uint32_t WindowsWindow::getHeight() const
{
    return m_data.height;
}

void WindowsWindow::setEventCallback(const WindowCallbackFunction& callback)
{
    m_data.callback = callback;
}

void* WindowsWindow::getNativeWindow() const
{
    return m_window;
}

}// namespace Meiosis