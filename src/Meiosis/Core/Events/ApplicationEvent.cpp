#include "Events/ApplicationEvent.hpp"

namespace Meiosis
{
WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}
}// namespace Meiosis