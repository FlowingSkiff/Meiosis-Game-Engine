#pragma once
#include "Core/Core.hpp"
namespace Meiosis
{
class ME_API Application
{
  public:
    Application();
    virtual ~Application();
    void run();
};
Meiosis::Application* CreateApplication();
}// namespace Meiosis
