#include <Genesis.hpp>
class MyNewApp : public Genesis::Application
{
  public:
    MyNewApp();
};

MyNewApp::MyNewApp()
{
    ENGINE_WARN("Created a new app!");
}

Genesis::Application* Genesis::CreateApplication()
{
    return new MyNewApp();
}