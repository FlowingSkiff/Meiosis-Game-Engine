#pragma once
#include "../../Core/Core.hpp"
#include "../../Core/Window.hpp"
#include "../../Core/GraphicsContext.hpp"
#include <glfw/glfw3.h>
namespace Meiosis
{
class ME_API WindowsWindow : public Window
{
  public:
    struct WindowData
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool is_vsync;
        WindowCallbackFunction callback;
    };

  public:
    WindowsWindow(const std::string& name = "Meiosis Engine", uint32_t width = 1600, uint32_t height = 900);
    virtual ~WindowsWindow();
    void onUpdate() override;
    auto getWidth() const -> uint32_t override;
    auto getHeight() const -> uint32_t override;
    void setEventCallback(const WindowCallbackFunction& callback) override;
    void setVSync(bool should_enabled) override;
    bool isVSync() const override;
    auto getNativeWindow() const -> void* override;

  private:
    GLFWwindow* m_window = nullptr;
    std::unique_ptr<GraphicsContext> m_context = nullptr;
    WindowData m_data;
};
}// namespace Meiosis