#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <memory>
#include <iostream>


struct GLFWWindowTerminator
{
    void operator()(GLFWwindow* /*window*/) const
    {
        glfwTerminate();
    }
};

using SmartGLFWWindow = std::unique_ptr<GLFWwindow, GLFWWindowTerminator>;

static void InitGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Processing input function
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

SmartGLFWWindow WindowInit()
{
    SmartGLFWWindow window(glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL));
    if (!window)
    {
        std::cout << "Failed to create GLFW window.\n";
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window.get());
    // initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD.\n";
        return nullptr;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    return window;
}

const int32_t NUM_PARTICLES = 1024 * 1024;
const int32_t WORK_GROUP_SIZE = 128;

struct pos
{
    float x, y, z, w;
    auto* begin() { return &x; }
    auto* end() { return &w + 1; }
};

struct vel
{
    float vx, vy, vz, vw;
    auto* begin() { return &vx; }
    auto* end() { return &vw + 1; }
};

struct color
{
    float r, g, b, a;
    auto* begin() { return &r; }
    auto* end() { return &a + 1; }
};

GLuint posSSbo;
GLuint velSSbo;
GLuint colSSbo;

template<typename Type>
Type* generateBufferObject(GLuint& gl_id)
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


int main()
{
    InitGLFW();
    SmartGLFWWindow window = std::move(WindowInit());


    if (!window.get())
    {
        return -1;
    }

    [[maybe_unused]] auto* vel_buffer = generateBufferObject<vel>(velSSbo);
    [[maybe_unused]] auto* pos_buffer = generateBufferObject<pos>(posSSbo);
    [[maybe_unused]] auto* col_buffer = generateBufferObject<color>(colSSbo);

    while (!glfwWindowShouldClose(window.get()))
    {
        processInput(window.get());

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }


    glfwTerminate();
}
