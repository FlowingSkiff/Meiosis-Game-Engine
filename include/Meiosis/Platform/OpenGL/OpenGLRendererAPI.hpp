#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/RendererAPI.hpp"

namespace Meiosis
{
class ME_API OpenGLRendererAPI : public RendererAPI
{
    virtual void init() override;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void setClearColor(const glm::vec4& color) override;
    virtual void clear() override;
    virtual API getAPI() override;

    virtual auto createIndexBuffer(const std::vector<uint32_t>& indicies) -> std::shared_ptr<IndexBuffer> override;
    virtual auto createVertexBuffer(const std::vector<float>& vertices) -> std::shared_ptr<VertexBuffer> override;
    virtual auto createVertexBuffer(size_t size) -> std::shared_ptr<VertexBuffer> override;
    virtual auto createVertexArray() -> std::shared_ptr<VertexArray> override;
    virtual auto createShader(const std::string& filename) -> std::shared_ptr<Shader> override;
    virtual auto createShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) -> std::shared_ptr<Shader> override;

    virtual void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f)) override;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& array, uint32_t count = 0) override;
};
}// namespace Meiosis