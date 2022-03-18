#include <Meiosis.hpp>
#include "ExampleTestLayer.hpp"
class MyNewApp : public Meiosis::Application
{
  public:
    MyNewApp();
};

MyNewApp::MyNewApp()
{
    pushLayer(new ExampleLayer());
}

Meiosis::Application* Meiosis::CreateApplication()
{
    return new MyNewApp();
}