#pragma once
#include "Event.hpp"
#include <cstdint>

namespace Genesis
{
class WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(uint32_t width, uint32_t height);
    inline auto getWidth() const { return m_width; }
    inline auto getHeight() const { return m_height; }
    static EventType getStaticType() { return EventType::WindowResize; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override { return static_cast<int>(EventCategory::Application); }

  private:
    uint32_t m_width;
    uint32_t m_height;
};
class WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent() = default;
    static EventType getStaticType() { return EventType::WindowClose; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override { return static_cast<int>(EventCategory::Application); }
};

class AppTickEvent : public Event
{
  public:
    AppTickEvent() = default;
    static EventType getStaticType() { return EventType::AppTick; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override { return static_cast<int>(EventCategory::Application); }
};
class AppUpdateEvent : public Event
{
  public:
    AppUpdateEvent() = default;
    static EventType getStaticType() { return EventType::AppUpdate; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override { return static_cast<int>(EventCategory::Application); }
};
class AppRenderEvent : public Event
{
  public:
    AppRenderEvent() = default;
    static EventType getStaticType() { return EventType::AppRender; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override { return static_cast<int>(EventCategory::Application); }
};
}// namespace Genesis