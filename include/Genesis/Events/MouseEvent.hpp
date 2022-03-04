#pragma once
#include "..\Core\Core.hpp"
#include "Event.hpp"
#include "..\Core\MouseCodes.hpp"
namespace Genesis
{
class MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(const float x, const float y);
    float getX() const { return m_x_offset; }
    float getY() const { return m_y_offset; }
    static EventType getStaticType() { return EventType::MouseMove; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override;

  private:
    float m_x_offset;
    float m_y_offset;
};
class MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent(const float x, const float y);
    float getX() const { return m_x_offset; }
    float getY() const { return m_y_offset; }
    static EventType getStaticType() { return EventType::MouseScroll; }
    virtual EventType type() const override { return getStaticType(); }
    virtual int categoryFlags() const override;

  private:
    float m_x_offset;
    float m_y_offset;
};
class MouseButtonEvent : public Event
{
  public:
    inline MouseCode mouseButton() const;
    virtual int categoryFlags() const override;

  protected:
    MouseButtonEvent(const MouseCode code);

  private:
    MouseCode m_code;
};
class MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(const MouseCode button);
    static EventType getStaticType() { return EventType::MouseButtonPress; }
    virtual EventType type() const override { return getStaticType(); }
};
class MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(const MouseCode button);
    static EventType getStaticType() { return EventType::MouseButtonRelease; }
    virtual EventType type() const override { return getStaticType(); }
};
}// namespace Genesis