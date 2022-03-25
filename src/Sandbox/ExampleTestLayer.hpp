#pragma once
#include <Meiosis.hpp>

class ExampleLayer : public Meiosis::Layer
{
  public:
    ExampleLayer(): m_float_val(1.0) {}
    virtual ~ExampleLayer() {}
    virtual void onEvent(Meiosis::Event& e) override;
    virtual void onImguiRender() override;
    private:
      float m_float_val;
};