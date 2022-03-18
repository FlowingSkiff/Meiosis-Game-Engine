#include "Events/KeyEvent.hpp"

namespace Meiosis
{
int KeyEvent::categoryFlags() const
{
    return static_cast<int>(EventCategory::Keyboard) | static_cast<int>(EventCategory::Input);
}

KeyEvent::KeyEvent(const KeyCode keycode) : m_key_code(keycode) {}
KeyPressedEvent::KeyPressedEvent(const KeyCode keycode, const uint16_t repeat_count) : KeyEvent(keycode), m_repeat_count(repeat_count) {}
KeyReleasedEvent::KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}
KeyTypedEvent::KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}
}// namespace Meiosis