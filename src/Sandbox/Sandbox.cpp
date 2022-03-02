#include <Genesis.hpp>
#include <iostream>
class MyNewApp : public Genesis::Application
{
  public:
    MyNewApp();
};

MyNewApp::MyNewApp()
{
    std::cout << "Created a new app!\n";
}

Genesis::Application* Genesis::CreateApplication()
{
    return new MyNewApp();
}