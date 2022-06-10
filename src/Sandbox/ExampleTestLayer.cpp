#include "ExampleTestLayer.hpp"
#include <imgui/imgui.h>
#include <vector>
#include <array>

bool ExampleLayer::onKeyPressEvent(Meiosis::KeyPressedEvent& e)
{
    switch (e.keyCode())
    {
        case Meiosis::KeyCode::Escape:
            Meiosis::Application::get().shouldExit();
            break;
        default:
            break;
    }
    return false;
}

void ExampleLayer::onEvent([[maybe_unused]] Meiosis::Event& e)
{
    // ENGINE_INFO("{}", e);
    Meiosis::EventHandler handler(e);
    handler.dispatch<Meiosis::KeyPressedEvent>(bindMemberFunction(this, &ExampleLayer::onKeyPressEvent));
}

void ExampleLayer::onImguiRender()
{
    ImGui::Text("dear imgui says hello. (%s)", IMGUI_VERSION);
    ImGui::InputFloat("Float value: ", &m_float_val);
    ImGui::InputFloat3("Float3", glm::value_ptr(m_simple_color));
    ImGui::Text(fmt::format("FPS: {:.2f}", 1 / m_last_frame_time).c_str());
}

void ExampleLayer::onUpdate([[maybe_unused]] Meiosis::Timestep dt)
{

    const float dx = dt.getSeconds();
    m_last_frame_time = dt.getSeconds();
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::W))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(0.0, -dx, 0.0));
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::S))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(0.0, dx, 0.0));
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::A))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(dx, 0.0, 0.0));
    if (Meiosis::Input::isKeyPressed(Meiosis::KeyCode::D))
        m_camera.setPosition(m_camera.getPosition() + glm::vec3(-dx, 0.0, 0.0));
    Meiosis::Renderer::beginScene(m_camera);
    Meiosis::Renderer::submit(m_shader_library.get(m_shader), m_obj);
    Meiosis::Renderer::submit(m_shader_library.get(m_texture_shader), m_texture_obj);

    Meiosis::Renderer::submit(m_simple_material, m_simple_obj);
    Meiosis::Renderer::endScene();
}

struct PosAndTexture
{
    std::array<float, 2> position;
    unsigned int texture_id;
    std::array<float, 2> texture_coord;
};

ExampleLayer::ExampleLayer() : m_float_val(1.0), m_obj(Meiosis::Renderer::createVertexArray()), m_texture_obj(Meiosis::Renderer::createVertexArray()), m_shader(), m_shader_library(), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_simple_obj(Meiosis::Renderer::createVertexArray()), m_simple_color{ 0.0, 0.0, 0.0 }
{
    // clang-format off
    std::vector<float> verticies{
        -0.5f, -0.5f, 0.8f, 0.1f, 0.1f, 
         0.0f, -0.5f, 0.1f, 0.8f, 0.1f, 
         0.0f,  0.0f, 0.1f, 0.1f, 0.8f, 
        -0.5f,  0.0f, 0.8f, 0.8f, 0.8f
    };
    // clang-format on
    auto vertex = Meiosis::Renderer::createVertexBuffer(verticies);
    Meiosis::BufferLayout layout{
        { "a_position", Meiosis::ShaderUniformType::Float2 },
        { "a_color", Meiosis::ShaderUniformType::Float3 }
    };
    vertex->setLayout(layout);
    m_obj->addVertexBuffer(vertex);
    auto inde = Meiosis::Renderer::createIndexBuffer({ 0, 1, 2, 2, 3, 0 });
    m_obj->setIndexBuffer(inde);
    // clang-format off
    const std::vector<PosAndTexture> text_verticies{
        {0.0f,  0.0f, 0U, 0.0f, 0.0f},
        {1.0f,  0.0f, 0U, 1.0f, 0.0f},
        {1.0f,  1.0f, 0U, 1.0f, 1.0f},
        {0.0f,  1.0f, 0U, 0.0f, 1.0f}
    };
    // clang-format on
    auto tex_vertex = Meiosis::Renderer::createVertexBuffer(text_verticies);
    Meiosis::BufferLayout texture_layout{
        { "a_position", Meiosis::ShaderUniformType::Float2 },
        { "a_texture_id", Meiosis::ShaderUniformType::UnsignedInt },
        { "a_texture_coord", Meiosis::ShaderUniformType::Float2 }
    };
    tex_vertex->setLayout(texture_layout);
    m_texture_obj->addVertexBuffer(tex_vertex);
    m_texture_obj->setIndexBuffer(inde);

    const std::string vertexSrc = R"....(
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

    const std::string fragmentSrc = R"....(
        #version 330 core
        layout (location = 0) out vec4 color;
        in vec3 v_position;
        in vec4 v_color;

        void main()
        {
            color = v_color;
        }
    )....";

    m_shader = m_shader_library.add(Meiosis::Renderer::createShader("Basic", vertexSrc, fragmentSrc));
    m_texture_shader = m_shader_library.load("resources/shaders/texture.glsl");
    m_texture = m_texture_library.load("resources/textures/grass.jpg");
    m_shader_library.get(m_texture_shader)->bind();
    m_shader_library.get(m_texture_shader)->setInt("u_texture", 0);
    m_texture_library.get(m_texture)->bind(0U);


    const std::vector<float> simple_color_vertices{ -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0, 1.0 };
    Meiosis::BufferLayout simple_layout{
        { "a_position", Meiosis::ShaderUniformType::Float2 }
    };
    auto simple_color_vertex = Meiosis::Renderer::createVertexBuffer(simple_color_vertices);
    simple_color_vertex->setLayout(simple_layout);
    m_simple_obj->addVertexBuffer(simple_color_vertex);
    m_simple_obj->setIndexBuffer(inde);
    m_simple_shader = m_shader_library.load("resources/shaders/simple_color.glsl");
    m_simple_material = Meiosis::Renderer::createMaterial(m_shader_library.get(m_simple_shader),
        [this](auto& shader) -> void {
            shader->setFloat3("u_color", m_simple_color);
        });
    m_texture_library.get(m_texture)->bind(0U);
}