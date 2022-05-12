#pragma once

#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/RendererAPI.hpp"
#include <memory>
#include "Meiosis/Renderer/Camera.hpp"
#include "Meiosis/Renderer/Texture.hpp"
namespace Meiosis
{
class ME_API Renderer
{
  public:
    static void init(RendererAPI::API api = RendererAPI::API::OpenGL);
    static void shutdown();

    static void onWindowResize(uint32_t width, uint32_t height);

    static void beginScene(Camera& cam);
    static void endScene();

    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void setClearColor(const glm::vec4& color);
    static void clear();
    static auto getAPI() -> RendererAPI::API;
    static auto getTime() -> float;

    static auto createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer>;
    static auto createVertexBuffer(const std::vector<float>& vertices) -> std::shared_ptr<VertexBuffer>;
    static auto createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer>;
    static auto createVertexArray() -> std::shared_ptr<VertexArray>;
    static auto createShader(const std::string& filename) -> std::shared_ptr<Shader>;
    static auto createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader>;
    static auto createTexture2D(const std::string& file_name) -> std::shared_ptr<Texture>;
    static auto createTexture2D(uint32_t width, uint32_t height) -> std::shared_ptr<Texture>;

    static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
    static void drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count = 0);

  private:
    static std::shared_ptr<RendererAPI> s_api_instance;
};// namespace Renderer
}// namespace Meiosis