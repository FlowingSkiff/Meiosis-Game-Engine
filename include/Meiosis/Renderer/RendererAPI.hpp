#pragma once
#include "Meiosis/Core/Core.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
namespace Meiosis
{
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Shader;
namespace RendererAPI
{
    enum class API {
        None = 0,
        OpenGL
    };

    void init();
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void setClearColor(const glm::vec4& color);
    void clear();
    API getAPI();

    auto createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer>;
    auto createVertexBuffer(const std::vector<float>& vertices) -> std::shared_ptr<VertexBuffer>;
    auto createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer>;
    auto createVertexArray() -> std::shared_ptr<VertexArray>;
    auto createShader(const std::string& filename) -> std::shared_ptr<Shader>;
    auto createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader>;

    void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
    void drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count = 0);
}// namespace RendererAPI
}// namespace Meiosis