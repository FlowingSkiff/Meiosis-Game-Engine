#include <Genesis.hpp>
class MyNewApp : public Genesis::Application
{
  public:
    MyNewApp();
};

MyNewApp::MyNewApp()
{
}

Genesis::Application* Genesis::CreateApplication()
{
    return new MyNewApp();
}