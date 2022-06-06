#pragma once
#include "Meiosis\Core\Core.hpp"
#include "Event.hpp"
#include "Meiosis\Core\MouseCodes.hpp"
namespace Meiosis
{
class ME_API MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(const float x, const float y);
    [[nodiscard]] float getX() const { return m_x_offset; }
    [[nodiscard]] float getY() const { return m_y_offset; }
    static EventType getStaticType() { return EventType::MouseMove; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }
    [[nodiscard]] virtual int categoryFlags() const override;

  private:
    float m_x_offset;
    float m_y_offset;
};
class ME_API MouseScrolledEvent : public Event
{
  public:
    MouseScrolledEvent(const float x, const float y);
    [[nodiscard]] float getX() const { return m_x_offset; }
    [[nodiscard]] float getY() const { return m_y_offset; }
    static EventType getStaticType() { return EventType::MouseScroll; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }
    [[nodiscard]] virtual int categoryFlags() const override;

  private:
    float m_x_offset;
    float m_y_offset;
};
class ME_API MouseButtonEvent : public Event
{
  public:
    [[nodiscard]] inline MouseCode mouseButton() const { return m_code; }
    [[nodiscard]] virtual int categoryFlags() const override;

  protected:
    explicit MouseButtonEvent(const MouseCode code);

  private:
    MouseCode m_code;
};
class ME_API MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    explicit MouseButtonPressedEvent(const MouseCode button);
    static EventType getStaticType() { return EventType::MouseButtonPress; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }
};
class ME_API MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    explicit MouseButtonReleasedEvent(const MouseCode button);
    static EventType getStaticType() { return EventType::MouseButtonRelease; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }
};
}// namespace Meiosis