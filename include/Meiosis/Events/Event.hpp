#pragma once
#include "../Core/Core.hpp"
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>

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


class ME_API Event
{
  protected:
    Event() : m_handled{ false } {}

  public:
    virtual ~Event() {}
    /**
     * @brief Gets the type of event
     *
     * @return EventType
     */
    virtual EventType type() const = 0;
    virtual int categoryFlags() const = 0;

  public:
    /**
     * @brief Determines if the event is in the current category
     *
     * @param cat category to check if the event is in
     * @return true The event is in the specified category
     * @return false The event is not in the specified category
     */
    bool isInCategory(EventCategory cat)
    {
        return categoryFlags() & static_cast<int>(cat);
    }
    /**
     * @brief Funtion to get the status of the event
     *
     * @param should_handle optional arg for whether to handle the event
     * @return true the event has been handled
     * @return false the event has not been handled
     */
    inline bool handle(bool should_handle = false) { return m_handled |= should_handle; }

  private:
    bool m_handled;
};

class ME_API EventHandler
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

template<>
struct fmt::formatter<Meiosis::Event>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }
    template<typename FormatContext>
    auto format(const Meiosis::Event& e, FormatContext& ctx)
    {
        return format_to(ctx.out(), "{}", magic_enum::enum_name(e.type()));
    }
};