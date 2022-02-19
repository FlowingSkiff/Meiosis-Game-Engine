#pragma once
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWWindowTerminator
{
    void operator()(GLFWwindow* window) const;
};

class Application
{
    using SmartGLFWWindow = std::unique_ptr<GLFWwindow, GLFWWindowTerminator>;

  public:
    static int run();

  private:
    static void initGLFW();
    static void framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height);
    static void processInput(GLFWwindow* window);
    static SmartGLFWWindow windowInit();

    constexpr static int GLFWVersionMajor = 4;
    constexpr static int GLFWVersionMinor = 3;
    constexpr static auto GLFWProfile = GLFW_OPENGL_CORE_PROFILE;
};