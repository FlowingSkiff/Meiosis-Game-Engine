#pragma once
#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include <memory>
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "../Layer/LayerStack.hpp"
namespace Meiosis
{
class ME_API Application
{
  public:
    Application();
    virtual ~Application();
    void run();
    void onEvent(Event& e);
    bool onWindowClose(WindowCloseEvent& e);
    bool onWindowResize(WindowResizeEvent& e);
  public:
    void pushLayer(Layer* layer);
  protected:
    std::unique_ptr<Window> m_window;
    bool m_running = true;
    LayerStack m_layers;
};
Meiosis::Application* CreateApplication();
}// namespace Meiosis
