#include "Core/Window.hpp"

#ifdef _WIN32
#include "Platform/Windows/WindowsWindow.hpp"
#else
#error "Windows is only supported."
#endif

namespace Meiosis
{
std::unique_ptr<Window> Window::create(const std::string& name, uint32_t width, uint32_t height)
{
#ifdef _WIN32
    return std::make_unique<WindowsWindow>(name, width, height);
#else
    return nullptr;
#endif
}
}// namespace Meiosis