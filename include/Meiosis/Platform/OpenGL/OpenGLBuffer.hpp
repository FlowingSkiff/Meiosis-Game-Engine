#pragma once

#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/RendererBuffer.hpp"
#include <glad/glad.h>
namespace Meiosis
{
class ME_API OpenGLVertexBuffer : public VertexBuffer
{
  public:
    explicit OpenGLVertexBuffer(const std::vector<float>& vertices);
    explicit OpenGLVertexBuffer(size_t size);
    explicit OpenGLVertexBuffer(const void* const data, std::size_t size);
    virtual ~OpenGLVertexBuffer();
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual void setData(const void* data, size_t size) override;
    virtual void setLayout(const BufferLayout& layout) override;
    virtual auto getLayout() const -> const BufferLayout& override { return m_layout; }

  private:
    uint32_t m_renderer_id;
    BufferLayout m_layout;
};

class ME_API OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(const std::vector<uint32_t>& indicies);
    virtual ~OpenGLIndexBuffer();
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual auto getCount() const -> uint32_t override { return m_count; }

  private:
    uint32_t m_renderer_id;
    uint32_t m_count;
};

class ME_API OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

  public:
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

    virtual auto getVertexBuffers() const -> const std::vector<std::shared_ptr<VertexBuffer>>& override { return m_vertex_buffers; }
    virtual auto getIndexBuffer() const -> const std::shared_ptr<IndexBuffer>& override { return m_index_buffer; }

  private:
    uint32_t m_renderer_id;
    uint32_t m_vertex_buffer_index;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;
};
}// namespace Meiosis