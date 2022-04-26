#include "Core/Window.hpp"

#ifdef MEIOSIS_BUILD_WINDOWS
#include "Platform/Windows/WindowsWindow.hpp"
#else
#error "Windows is only supported."
#endif

namespace Meiosis
{
std::unique_ptr<Window> Window::create(const std::string& name, uint32_t width, uint32_t height)
{
#ifdef MEIOSIS_BUILD_WINDOWS
    return std::make_unique<WindowsWindow>(name, width, height);
#else
    return nullptr;
#endif
}
}// namespace Meiosis