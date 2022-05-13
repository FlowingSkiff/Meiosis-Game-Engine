#include "Meiosis/Platform/OpenGL/OpenGLRendererAPI.hpp"
#include "glad/glad.h"
#include "Meiosis/Platform/OpenGL/OpenGLBuffer.hpp"
#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
#include "Meiosis/Platform/OpenGL/OpenGLTexture.hpp"
#include <glfw/glfw3.h>
namespace Meiosis//::RendererAPI::
{

void debugMessageCallback([[maybe_unused]] GLenum source, [[maybe_unused]] GLenum type, [[maybe_unused]] GLuint id, [[maybe_unused]] GLenum severity, [[maybe_unused]] GLsizei length, [[maybe_unused]] const GLchar* message, [[maybe_unused]] const void* userParam)
{
    ME_ENGINE_DEBUG("OpenGL Debug Callback: ({}) {}", source, std::string(message, static_cast<size_t>(length)));
}

void OpenGLRendererAPI::init()
{
    glEnable(GL_BLEND);
    glEnable(GL_DEBUG_OUTPUT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback(debugMessageCallback, nullptr);
}
void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(static_cast<GLsizei>(x), static_cast<GLsizei>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}
void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRendererAPI::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
RendererAPI::API OpenGLRendererAPI::getAPI() { return API::OpenGL; }

auto OpenGLRendererAPI::createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer>
{
    return std::make_shared<OpenGLIndexBuffer>(indicies);
}
auto OpenGLRendererAPI::createVertexBuffer(const std::vector<float>& vertices) -> std::shared_ptr<VertexBuffer>
{
    return std::make_shared<OpenGLVertexBuffer>(vertices);
}
auto OpenGLRendererAPI::createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer>
{
    return std::make_shared<OpenGLVertexBuffer>(size);
}

auto OpenGLRendererAPI::createVertexArray() -> std::shared_ptr<VertexArray>
{
    return std::make_shared<OpenGLVertexArray>();
}

void OpenGLRendererAPI::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
    shader->bind();
    shader->setMat4("u_transform", transform);
    shader->setMat4("u_view_projection", m_view_projection_matrix);

    vertexArray->bind();
    drawIndexed(vertexArray);
}

void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count)
{
    count = (count) ? count : array->getIndexBuffer()->getCount();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    // glBindTexture(GL_TEXTURE_2D, 0);
}


auto OpenGLRendererAPI::createShader(const std::string& filename) -> std::shared_ptr<Shader>
{
    return std::make_shared<OpenGLShader>(filename);
}
auto OpenGLRendererAPI::createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader>
{
    return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
}

void OpenGLRendererAPI::beginScene(Camera& camera)
{
    m_view_projection_matrix = camera.getViewProjectionMatrix();
}
void OpenGLRendererAPI::endScene()
{
}


auto OpenGLRendererAPI::createTexture2D(const std::string& file_name) -> std::shared_ptr<Texture>
{
    return std::make_shared<OpenGLTexture2D>(file_name);
}
auto OpenGLRendererAPI::createTexture2D(uint32_t width, uint32_t height) -> std::shared_ptr<Texture>
{
    return std::make_shared<OpenGLTexture2D>(width, height);
}

auto OpenGLRendererAPI::getTime() const -> float
{
    return static_cast<float>(glfwGetTime());
}

}// namespace Meiosis