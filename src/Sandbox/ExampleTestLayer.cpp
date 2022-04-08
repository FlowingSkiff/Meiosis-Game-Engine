#include "ExampleTestLayer.hpp"
#include <imgui/imgui.h>
#include <vector>

bool ExampleLayer::onKeyPressEvent(Meiosis::KeyPressedEvent& e)
{
    switch (e.keyCode())
    {
        case Meiosis::KeyCode::Escape:
            Meiosis::Application::get().shouldExit();
    }
    return false;
}

void ExampleLayer::onEvent(Meiosis::Event& e)
{
    ENGINE_INFO("{}", e);
    Meiosis::EventHandler handler(e);
    handler.dispatch<Meiosis::KeyPressedEvent>(bindMemberFunction(this, &ExampleLayer::onKeyPressEvent));
}

void ExampleLayer::onImguiRender()
{
    ImGui::Text("dear imgui says hello. (%s)", IMGUI_VERSION);
    ImGui::InputFloat("Float value: ", &m_float_val);
}

void ExampleLayer::onUpdate(float dt)
{
    const float dx = 0.1f;
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::W))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(0.0, -dx, 0.0));
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::S))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(0.0, dx, 0.0));
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::A))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(dx, 0.0, 0.0));
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::D))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(-dx, 0.0, 0.0));
    m_shader->setMat4("u_view_projection", m_camera.getViewProjectionMatrix());
    Meiosis::Renderer::submit(m_shader, m_obj);
}

ExampleLayer::ExampleLayer() : m_float_val(1.0), m_obj(), m_shader(), m_shader_library(), m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
    m_obj = Meiosis::Renderer::createVertexArray();
    // clang-format off
    std::vector<float> verticies{
        -0.5, -0.5, 0.8, 0.1, 0.1, 
         0.5, -0.5, 0.1, 0.8, 0.1, 
         0.5,  0.5, 0.1, 0.1, 0.8, 
        -0.5,  0.5, 0.8, 0.8, 0.8
    };
    // clang-format on
    auto vertex = Meiosis::Renderer::createVertexBuffer(verticies);
    Meiosis::BufferLayout layout = {
        { "a_position", Meiosis::ShaderUniformType::Float2 },
        { "a_color", Meiosis::ShaderUniformType::Float3 }
    };
    vertex->setLayout(layout);
    m_obj->addVertexBuffer(vertex);
    auto inde = Meiosis::Renderer::createIndexBuffer({ 0, 1, 2, 2, 3, 0 });
    m_obj->setIndexBuffer(inde);

    std::string vertexSrc = R"....(
        #version 330 core
        layout(location = 0) in vec2 a_position;
        layout(location = 1) in vec3 a_color;
        uniform mat4 u_transform;
        uniform mat4 u_view_projection;

        out vec3 v_position;
        out vec4 v_color;
        void main()
        {
            v_position =  vec3(a_position, 1.0);
            v_color = vec4(a_color, 1.0);
            gl_Position = u_view_projection * u_transform * vec4(a_position, 0.0, 1.0);
            // gl_Position = vec4(a_position, 0.0, 1.0);
        }
    )....";

    std::string fragmentSrc = R"....(
        #version 330 core
        layout (location = 0) out vec4 color;
        in vec3 v_position;
        in vec4 v_color;

        void main()
        {
            color = v_color;
        }
    )....";

    m_shader = Meiosis::Renderer::createShader("Basic", vertexSrc, fragmentSrc);
}