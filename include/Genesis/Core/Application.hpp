#pragma once
#include "Core/Core.hpp"
namespace Genesis
{
class GN_API Application
{
  public:
    Application();
    virtual ~Application();
    void print();
    void run();
};
Genesis::Application* CreateApplication();
}// namespace Genesis
