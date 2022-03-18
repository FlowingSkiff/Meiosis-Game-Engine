#pragma once
#include "..\Core\Core.hpp"
#include "Event.hpp"
#include "..\Core\Keycodes.hpp"
namespace Meiosis
{
class ME_API KeyEvent : public Event
{
  public:
    inline KeyCode keyCode() const { return m_key_code; }
    virtual int categoryFlags() const override;

  protected:
    KeyEvent(const KeyCode keycode);
    KeyCode m_key_code;
};

class ME_API KeyPressedEvent : public KeyEvent
{
  public:
    KeyPressedEvent(const KeyCode keycode, const uint16_t repeat_count);

  public:
    auto repeatCount() const { return m_repeat_count; }

    inline static EventType getStaticType() { return EventType::KeyPress; }
    virtual EventType type() const override { return getStaticType(); }

  private:
    uint16_t m_repeat_count;
};

class ME_API KeyReleasedEvent : public KeyEvent
{
  public:
    KeyReleasedEvent(const KeyCode keycode);
    inline static EventType getStaticType() { return EventType::KeyRelease; }
    virtual EventType type() const override { return getStaticType(); }
};

class ME_API KeyTypedEvent : public KeyEvent
{
  public:
    KeyTypedEvent(const KeyCode keycode);
    static EventType getStaticType() { return EventType::KeyType; }
    virtual EventType type() const override { return getStaticType(); }
};
}// namespace Meiosis