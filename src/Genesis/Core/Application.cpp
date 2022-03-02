#include "Core/Application.hpp"
#include "Core/Log/Log.hpp"
namespace Genesis
{
Application::Application() {}
Application::~Application() {}
void Application::print() { ENGINE_WARN("Printing!"); }
void Application::run()
{
    this->print();
}
}// namespace Genesis