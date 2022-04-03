#include "Meiosis/Renderer/RendererAPI.hpp"
#include "glad/glad.h"
#include "Meiosis/Platform/OpenGL/OpenGLBuffer.hpp"
#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
namespace Meiosis::RendererAPI
{

void debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    ME_ENGINE_DEBUG("OpenGL Debug Callback: ({}) {}", source, std::string(message, length));
}

void init()
{
    glEnable(GL_BLEND);
    glEnable(GL_DEBUG_OUTPUT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback(debugMessageCallback, nullptr);
}
void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}
void setClearColor(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}
void clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
API getAPI() { return API::OpenGL; }

auto createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer>
{
    return std::make_shared<OpenGLIndexBuffer>(indicies);
}
auto createVertexBuffer(const std::vector<float>& vertices) -> std::shared_ptr<VertexBuffer>
{
    return std::make_shared<OpenGLVertexBuffer>(vertices);
}
auto createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer>
{
    return std::make_shared<OpenGLVertexBuffer>(size);
}

auto createVertexArray() -> std::shared_ptr<VertexArray>
{
    return std::make_shared<OpenGLVertexArray>();
}

void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
    shader->bind();
    shader->setMat4("u_transform", transform);

    vertexArray->bind();
    drawIndexed(vertexArray);
}

void drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count)
{
    count = (count) ? count : array->getIndexBuffer()->getCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}


auto createShader(const std::string& filename) -> std::shared_ptr<Shader>
{
    return std::make_shared<OpenGLShader>(filename);
}
auto createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader>
{
    return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
}

}// namespace Meiosis::RendererAPI