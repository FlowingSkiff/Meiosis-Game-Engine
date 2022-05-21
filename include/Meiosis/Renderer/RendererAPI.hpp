#pragma once
#include "Meiosis/Core/Core.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Meiosis/Renderer/Camera.hpp"
#include "Meiosis/Renderer/Texture.hpp"
namespace Meiosis
{
class IndexBuffer;
class VertexBuffer;
class VertexArray;
class Shader;
// namespace RendererAPI
class ME_API RendererAPI
{
  public:
    enum class API {
        None = 0,
        OpenGL
    };
    virtual ~RendererAPI() = default;
    virtual void init() = 0;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void setClearColor(const glm::vec4& color) = 0;
    virtual void clear() = 0;
    virtual API getAPI() = 0;

    virtual auto createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer> = 0;
    virtual auto createVertexBuffer(const std::vector<float>& vertices) -> std::shared_ptr<VertexBuffer> = 0;
    virtual auto createVertexBuffer(const void const* data, std::size_t size) -> std::shared_ptr<VertexBuffer> = 0;
    virtual auto createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer> = 0;
    virtual auto createVertexArray() -> std::shared_ptr<VertexArray> = 0;
    virtual auto createShader(const std::string& filename) -> std::shared_ptr<Shader> = 0;
    virtual auto createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader> = 0;
    virtual auto createTexture2D(const std::string& file_name) -> std::shared_ptr<Texture> = 0;
    virtual auto createTexture2D(uint32_t width, uint32_t height) -> std::shared_ptr<Texture> = 0;

    virtual void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f)) = 0;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count = 0) = 0;
    virtual void beginScene(Camera& cam) = 0;
    virtual void endScene() = 0;

    virtual auto getTime() const -> float = 0;
};// namespace RendererAPI
}// namespace Meiosis