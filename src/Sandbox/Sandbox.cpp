#include <Meiosis.hpp>
class MyNewApp : public Meiosis::Application
{
  public:
    MyNewApp();
};

MyNewApp::MyNewApp()
{
    ENGINE_TRACE("Test ");
    ENGINE_DEBUG("Test ");
    ENGINE_INFO("Test ");
    ENGINE_WARN("Test ");
    ENGINE_ERROR("Test ");
}

Meiosis::Application* Meiosis::CreateApplication()
{
    return new MyNewApp();
}