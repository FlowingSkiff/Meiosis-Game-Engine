#include "Core/Application.hpp"
#include "Core/Log.hpp"
#include "Core/Window.hpp"
namespace Meiosis
{
Application::Application()
{
    m_window = Window::create();
    m_window->setEventCallback(ME_BIND_EVENT_FN(Application::onEvent));
}
Application::~Application()
{
}
void Application::run()
{
    while (m_running)
    {
        for (auto layer : m_layers)
            layer->onUpdate(0.0f);
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
}
}// namespace Meiosis