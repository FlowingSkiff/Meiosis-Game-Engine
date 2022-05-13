#pragma once
#include <Meiosis.hpp>

class ExampleLayer : public Meiosis::Layer
{
  public:
    ExampleLayer();
    virtual ~ExampleLayer() {}
    virtual void onEvent(Meiosis::Event& e) override;
    virtual void onImguiRender() override;
    virtual void onUpdate(Meiosis::Timestep dt) override;
    bool onKeyPressEvent(Meiosis::KeyPressedEvent& e);

  private:
    float m_float_val;
    std::shared_ptr<Meiosis::VertexArray> m_obj;
    std::shared_ptr<Meiosis::VertexArray> m_texture_obj;
    std::shared_ptr<Meiosis::Shader> m_shader;
    Meiosis::ShaderLibrary m_shader_library;
    Meiosis::Camera2D m_camera;
    std::shared_ptr<Meiosis::Shader> m_texture_shader;
    std::shared_ptr<Meiosis::Texture> m_texture;
    std::shared_ptr<Meiosis::VertexArray> m_simple_obj;
    std::shared_ptr<Meiosis::Shader> m_simple_shader;
    glm::vec3 m_simple_color;
    float m_last_frame_time = 1.f;
};