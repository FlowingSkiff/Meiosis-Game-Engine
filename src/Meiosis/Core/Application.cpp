#include "Core/Application.hpp"
#include "Core/Log.hpp"
#include "Core/Window.hpp"
namespace Meiosis
{

Application* Application::s_instance = nullptr;
Application::Application()
{
    s_instance = this;
    m_window = Window::create();
    m_window->setEventCallback(ME_BIND_EVENT_FN(Application::onEvent));

    m_imgui_layer = new ImguiLayer();
    pushOverlay(m_imgui_layer);
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
    handler.dispatch<WindowCloseEvent>(ME_BIND_EVENT_FN(Application::onWindowClose));
    handler.dispatch<WindowResizeEvent>(ME_BIND_EVENT_FN(Application::onWindowResize));

    for (auto rit = m_layers.rbegin(); rit != m_layers.rend(); ++rit)
    {
        if (e.handle())
            break;
        (*rit)->onEvent(e);
    }
}

bool Application::onWindowClose(WindowCloseEvent& event)
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
}// namespace Meiosis