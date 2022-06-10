#include "Meiosis/Renderer/Renderer.hpp"
#include "Meiosis/Renderer/RendererAPI.hpp"
#include "Meiosis/Platform/OpenGL/OpenGLRendererAPI.hpp"
#include "Meiosis/Core/Log.hpp"
namespace Meiosis
{

std::shared_ptr<RendererAPI> Renderer::s_api_instance = nullptr;

void Renderer::init(RendererAPI::API api)
{
    switch (api)
    {
        case RendererAPI::API::OpenGL:
            s_api_instance = std::make_shared<OpenGLRendererAPI>();
            break;
        default:
            ME_ENGINE_ERROR("Unknown Renderer {}, defaulting to OpenGL", static_cast<int>(api));
            s_api_instance = std::make_shared<OpenGLRendererAPI>();
    }
    s_api_instance->init();
}
void Renderer::shutdown()
{
    // s_api_instance->shutdown();
}

void Renderer::onWindowResize(uint32_t width, uint32_t height)
{
    s_api_instance->setViewport(0, 0, width, height);
}

void Renderer::beginScene(Camera& camera)
{
    s_api_instance->beginScene(camera);
}

void Renderer::endScene()
{
    s_api_instance->endScene();
}

void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    s_api_instance->setViewport(x, y, width, height);
}
void Renderer::setClearColor(const glm::vec4& color)
{
    s_api_instance->setClearColor(color);
}
void Renderer::clear()
{
    s_api_instance->clear();
}
auto Renderer::getAPI() -> RendererAPI::API
{
    return s_api_instance->getAPI();
}

auto Renderer::createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer>
{
    return s_api_instance->createIndexBuffer(indicies);
}
auto Renderer::createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer>
{
    return s_api_instance->createVertexBuffer(size);
}
auto Renderer::createVertexArray() -> std::shared_ptr<VertexArray>
{
    return s_api_instance->createVertexArray();
}
auto Renderer::createShader(const std::string& filename) -> std::shared_ptr<Shader>
{
    return s_api_instance->createShader(filename);
}
auto Renderer::createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader>
{
    return s_api_instance->createShader(name, vertexSrc, fragmentSrc);
}

auto Renderer::createMaterial(const std::string& filename) -> Material
{
    return Material(s_api_instance->createShader(filename));
}
auto Renderer::createMaterial(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> Material
{
    return Material(s_api_instance->createShader(name, vertexSrc, fragmentSrc));
}
auto Renderer::createMaterial(std::shared_ptr<Shader>& shader) -> Material
{
    return Material(shader);
}
auto Renderer::createMaterial(std::shared_ptr<Shader>& shader, Material::UniformFunction function) -> Material
{
    return Material(shader, function);
}

auto Renderer::createMaterial(std::shared_ptr<Shader>&& shader) -> Material
{
    return Material(shader);
}
auto Renderer::createMaterial(std::shared_ptr<Shader>&& shader, Material::UniformFunction function) -> Material
{
    return Material(shader, function);
}

void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
    s_api_instance->submit(shader, vertexArray, transform);
}
void Renderer::submit(Material& material, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
    s_api_instance->submit(material.getShader(), vertexArray, transform);
}
void Renderer::drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count)
{
    s_api_instance->drawIndexed(array, count);
}

auto Renderer::createTexture2D(const std::string& file_name) -> std::shared_ptr<Texture>
{
    return s_api_instance->createTexture2D(file_name);
}
auto Renderer::createTexture2D(uint32_t width, uint32_t height) -> std::shared_ptr<Texture>
{
    return s_api_instance->createTexture2D(width, height);
}

auto Renderer::getTime() -> float
{
    return s_api_instance->getTime();
}

}// namespace Meiosis