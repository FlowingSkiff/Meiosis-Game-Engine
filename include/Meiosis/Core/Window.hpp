#pragma once

#include "Core.hpp"
#include "../Events/Event.hpp"
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
namespace Meiosis
{
class ME_API Window
{
  public:
    using WindowCallbackFunction = std::function<void(Event&)>;

  public:
    virtual ~Window() = default;
    virtual void onUpdate() = 0;
    virtual auto getWidth() const -> uint32_t = 0;
    virtual auto getHeight() const -> uint32_t = 0;
    virtual void setEventCallback(const WindowCallbackFunction& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual auto isVSync() const -> bool = 0;
    virtual auto getNativeWindow() const -> void* = 0;
    static std::unique_ptr<Window> create(const std::string& rhs = "Meiosis Engine", uint32_t width = 1600, uint32_t height = 900);

  protected:
    Window() {}
};
}// namespace Meiosis