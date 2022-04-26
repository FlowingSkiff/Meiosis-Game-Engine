#include "Core/Application.hpp"
#include "Core/Log.hpp"
#include "Core/Window.hpp"
#include "Meiosis/Renderer/Renderer.hpp"
#include "Meiosis/Renderer/RendererAPI.hpp"
namespace Meiosis
{

Application* Application::s_instance = nullptr;
Application::Application()
{
    s_instance = this;
    m_window = Window::create();
    m_window->setEventCallback(bindMemberFunction(this, &Application::onEvent));

    m_imgui_layer = new ImguiLayer();
    pushOverlay(m_imgui_layer);
    Renderer::init();
}
Application::~Application()
{
}

Application& Application::get()
{
    return *s_instance;
}
void Application::run()
{
    while (m_running)
    {
        Renderer::clear();
        for (auto layer : m_layers)
            layer->onUpdate(0.0f);
        m_imgui_layer->beginFrame();
        {
            for (auto layer : m_layers)
                layer->onImguiRender();
        }
        m_imgui_layer->endFrame();
        m_window->onUpdate();
    }
}

void Application::onEvent(Event& e)
{
    EventHandler handler(e);
    handler.dispatch<WindowCloseEvent>(bindMemberFunction(this, &Application::onWindowClose));
    handler.dispatch<WindowResizeEvent>(bindMemberFunction(this, &Application::onWindowResize));

    for (auto rit = m_layers.rbegin(); rit != m_layers.rend(); ++rit)
    {
        if (e.handle())
            break;
        (*rit)->onEvent(e);
    }
}

bool Application::onWindowClose([[maybe_unused]] WindowCloseEvent& event)
{
    m_running = false;
    return true;
}
bool Application::onWindowResize(WindowResizeEvent& e)
{
    if (e.getWidth() == 0 || e.getHeight() == 0)
    {
        return false;
    }
    return false;
}
void Application::pushLayer(Layer* layer)
{
    m_layers.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* layer)
{
    m_layers.pushOverlay(layer);
    layer->onAttach();
}

auto Application::getWindow() -> Window&
{
    return *m_window;
}
void Application::shouldExit()
{
    m_running = false;
}
}// namespace Meiosis