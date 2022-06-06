#pragma once
#include "Meiosis\Core\Core.hpp"
#include "Event.hpp"
#include "Meiosis\Core\KeyCodes.hpp"
namespace Meiosis
{
class ME_API KeyEvent : public Event
{
  public:
    [[nodiscard]] inline KeyCode keyCode() const { return m_key_code; }
    [[nodiscard]] virtual int categoryFlags() const override;

  protected:
    explicit KeyEvent(const KeyCode keycode);
    KeyCode m_key_code;
};

class ME_API KeyPressedEvent : public KeyEvent
{
  public:
    KeyPressedEvent(const KeyCode keycode, const uint16_t repeat_count);

  public:
    [[nodiscard]] auto repeatCount() const { return m_repeat_count; }

    inline static EventType getStaticType() { return EventType::KeyPress; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }

  private:
    uint16_t m_repeat_count;
};

class ME_API KeyReleasedEvent : public KeyEvent
{
  public:
    explicit KeyReleasedEvent(const KeyCode keycode);
    inline static EventType getStaticType() { return EventType::KeyRelease; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }
};

class ME_API KeyTypedEvent : public KeyEvent
{
  public:
    explicit KeyTypedEvent(const KeyCode keycode);
    static EventType getStaticType() { return EventType::KeyType; }
    [[nodiscard]] virtual EventType type() const override { return getStaticType(); }
};
}// namespace Meiosis