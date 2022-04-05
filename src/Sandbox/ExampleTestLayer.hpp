#pragma once
#include <Meiosis.hpp>

class ExampleLayer : public Meiosis::Layer
{
  public:
    ExampleLayer();
    virtual ~ExampleLayer() {}
    virtual void onEvent(Meiosis::Event& e) override;
    virtual void onImguiRender() override;
    virtual void onUpdate(float dt) override;
    bool onKeyPressEvent(Meiosis::KeyPressedEvent& e);

  private:
    float m_float_val;
    std::shared_ptr<Meiosis::VertexArray> m_obj;
    std::shared_ptr<Meiosis::Shader> m_shader;
    Meiosis::ShaderLibrary m_shader_library;
};