#include <Genesis.hpp>
class MyNewApp : public Genesis::Application
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

Genesis::Application* Genesis::CreateApplication()
{
    return new MyNewApp();
}