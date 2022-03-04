#include "Events/ApplicationEvent.hpp"

namespace Genesis
{
WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}
}// namespace Genesis