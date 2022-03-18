#pragma once
#include <Meiosis.hpp>

class ExampleLayer : public Meiosis::Layer
{
  public:
    ExampleLayer() {}
    virtual ~ExampleLayer() {}
    virtual void onEvent(Meiosis::Event& e);
};