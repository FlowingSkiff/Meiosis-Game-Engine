#pragma once
#include "../Core/Core.hpp"

namespace Meiosis
{

enum class EventType {
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMove,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPress,
    KeyRelease,
    KeyType,
    MouseButtonPress,
    MouseButtonRelease,
    MouseMove,
    MouseScroll
};

enum class EventCategory {
    None = 0,
    Application = bit(0),
    Input = bit(1),
    Keyboard = bit(2),
    Mouse = bit(3),
    MouseButton = bit(4)
};


class Event
{
  protected:
    Event() : m_handled{ false } {}

  public:
    virtual ~Event() {}
    virtual EventType type() const = 0;
    virtual int categoryFlags() const = 0;

  public:
    bool isInCategory(EventCategory cat)
    {
        return categoryFlags() & static_cast<int>(cat);
    }
    inline bool handle(bool should_handle) { return m_handled |= should_handle; }

  private:
    bool m_handled;
};

class EventHandler
{
  public:
    EventHandler(Event& event) : m_event(&event) {}
    template<typename TYPE, typename FUNC>
    bool dispatch(const FUNC& func);

  private:
    Event* m_event = nullptr;
};

template<typename TYPE, typename FUNC>
bool EventHandler::dispatch(const FUNC& func)
{
    bool should_handle = m_event->type() == TYPE::getStaticType();
    if (should_handle)
    {
        m_event->handle(func(static_cast<TYPE&>(*m_event)));
    }
    return should_handle;
}
}// namespace Meiosis