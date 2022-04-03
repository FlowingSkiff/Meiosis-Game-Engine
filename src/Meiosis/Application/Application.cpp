#include "Meiosis/Application/Application.hpp"

#include "Meiosis/OGLAbstraction/Renderer.hpp"
#include "Meiosis/OGLAbstraction/Texture.hpp"
#include "Meiosis/OGLAbstraction/ComputeShader.hpp"
#include "Meiosis/Core/Log/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Meiosis/Util/Vector.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void GLFWWindowTerminator::operator()(GLFWwindow* /*window*/) const
{
    glfwTerminate();
}

void Application::initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFWProfile);
}

void Application::framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Processing input function
void Application::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

Application::SmartGLFWWindow Application::windowInit()
{
    SmartGLFWWindow window(glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL));
    if (!window)
    {
        ENGINE_ERROR("Failed to create GLFW window.");
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window.get());
    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ENGINE_ERROR("Failed to initialize GLAD.");
        return nullptr;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window.get(), framebufferSizeCallback);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    return window;
}

const int32_t NUM_PARTICLES = 1024 * 1024;
const int32_t WORK_GROUP_SIZE = 128;

using pos = Util::Vector<float, 4>;
using vel = Util::Vector<float, 4>;
using color = Util::Vector<float, 4>;

GLuint posSSbo;
GLuint velSSbo;
GLuint colSSbo;

template<typename Type>
static Type* generateBufferObject(GLuint& gl_id)
{
    glGenBuffers(1, &gl_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, gl_id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(Type), NULL, GL_STATIC_DRAW);

    GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

    Type* buffer = static_cast<Type*>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(Type), bufMask));

    for (auto i = 0u; i < NUM_PARTICLES; ++i)
    {
        std::fill(buffer[i].begin(), buffer[i].end(), 0.f);
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    return buffer;
}

static void runComputeShader(GLuint computeShaderProgram)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, posSSbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, velSSbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, colSSbo);

    glUseProgram(computeShaderProgram);
    glDispatchCompute(NUM_PARTICLES / WORK_GROUP_SIZE, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}


int Application::run()
{
    initGLFW();
    SmartGLFWWindow window = std::move(windowInit());
    Logger::Init();
    ENGINE_INFO("Testing {}", 1.0);
    if (!window.get())
    {
        ENGINE_ERROR("Could not  initialize window");
        return -1;
    }

    [[maybe_unused]] auto* vel_buffer = generateBufferObject<vel>(velSSbo);
    [[maybe_unused]] auto* pos_buffer = generateBufferObject<pos>(posSSbo);
    [[maybe_unused]] auto* col_buffer = generateBufferObject<color>(colSSbo);

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };
    uint32_t indices[] = {
        0, 1, 2, 2, 3, 0
    };

    // ComputeShader compute_shader("resources/shaders/compute_move.shader");
    // auto vel_buffer = compute_shader.generateBufferObject<glm::vec4>(NUM_PARTICLES);
    // auto pos_buffer = compute_shader.generateBufferObject<glm::vec4>(NUM_PARTICLES);
    // auto col_buffer = compute_shader.generateBufferObject<glm::vec4>(NUM_PARTICLES);

    VertexArray vao;
    vao.Bind();
    VertexBuffer vb(positions, 4 * 5 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    vao.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    Shader shader("resources/shaders/ortho.shader");

    Texture texture("resources/textures/boat.png");
    texture.Bind();

    shader.SetUniform1i("u_Texture", 0);

    shader.Bind();
    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    shader.SetUniformMat4f("u_MVP", proj);

    const char* glsl_version = "#version 140";
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (!glfwWindowShouldClose(window.get()))
    {
        processInput(window.get());
        Renderer::Clear();
        Renderer::Draw(vao, ib, shader);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Hello world!");
        ImGui::Button("Button1");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}