#pragma once
#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include <memory>
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "../Layer/LayerStack.hpp"

#include "Meiosis/imgui/ImguiLayer.hpp"

int main(int argc, char** argv);

namespace Meiosis
{
class ME_API Application
{
  public:
    explicit Application();
    virtual ~Application();
    void onEvent(Event& e);
    bool onWindowClose(WindowCloseEvent& e);
    bool onWindowResize(WindowResizeEvent& e);
    void run();
    static Application& get();
    auto getWindow() -> Window&;
    void shouldExit();

  public:
    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);

  private:
    static Application* s_instance;
    friend int ::main(int argc, char** argv);

  protected:
    ImguiLayer* m_imgui_layer = nullptr;
    std::unique_ptr<Window> m_window;
    bool m_running = true;
    LayerStack m_layers;
};
Meiosis::Application* CreateApplication();
}// namespace Meiosis
