#include "Events\MouseEvent.hpp"

namespace Genesis
{
MouseMovedEvent::MouseMovedEvent(const float x, const float y) : m_x_offset(x), m_y_offset(y) {}
int MouseMovedEvent::categoryFlags() const
{
    return static_cast<int>(EventCategory::Mouse) | static_cast<int>(EventCategory::Input);
}
MouseScrolledEvent::MouseScrolledEvent(const float x, const float y) : m_x_offset(x), m_y_offset(y) {}
int MouseScrolledEvent::categoryFlags() const
{
    return static_cast<int>(EventCategory::Mouse) | static_cast<int>(EventCategory::Input);
}
MouseButtonEvent::MouseButtonEvent(const MouseCode code) : m_code(code) {}
MouseCode MouseButtonEvent::mouseButton() const { return m_code; }
int MouseButtonEvent::categoryFlags() const
{
    return static_cast<int>(EventCategory::Mouse) | static_cast<int>(EventCategory::Input) | static_cast<int>(EventCategory::MouseButton);
}
MouseButtonPressedEvent::MouseButtonPressedEvent(const MouseCode code) : MouseButtonEvent(code) {}
MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseCode code) : MouseButtonEvent(code) {}
}// namespace Genesis