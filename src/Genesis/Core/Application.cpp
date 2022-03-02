#include "Core/Application.hpp"
#include <iostream>
namespace Genesis
{
Application::Application() {}
Application::~Application() {}
void Application::print() { std::cout << "Hello world\n"; }
void Application::run()
{
    this->print();
}
}// namespace Genesis