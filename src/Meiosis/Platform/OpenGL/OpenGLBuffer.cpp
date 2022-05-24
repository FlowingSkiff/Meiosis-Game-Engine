#include "Meiosis/Platform/OpenGL/OpenGLBuffer.hpp"

namespace Meiosis
{

static auto toOpenGLBaseType(ShaderUniformType type) -> GLenum
{
    switch (type)
    {
        case ShaderUniformType::None:
            return 0;
            break;
        case ShaderUniformType::Float:
            return GL_FLOAT;
            break;
        case ShaderUniformType::Float2:
            return GL_FLOAT;
            break;
        case ShaderUniformType::Float3:
            return GL_FLOAT;
            break;
        case ShaderUniformType::Float4:
            return GL_FLOAT;
            break;
        case ShaderUniformType::Mat3:
            return GL_FLOAT;
            break;
        case ShaderUniformType::Mat4:
            return GL_FLOAT;
            break;
        case ShaderUniformType::Int:
            return GL_INT;
            break;
        case ShaderUniformType::Int2:
            return GL_INT;
            break;
        case ShaderUniformType::Int3:
            return GL_INT;
            break;
        case ShaderUniformType::Int4:
            return GL_INT;
            break;
        case ShaderUniformType::Bool:
            return GL_BOOL;
            break;
        case ShaderUniformType::UnsignedInt:
            return GL_UNSIGNED_INT;
            break;
    }
    ME_ENGINE_ERROR("Unrecognized uniform type {}", static_cast<int>(type));
    return 0;
}
OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& vertices)
{
    glCreateBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * vertices.size()), vertices.data(), GL_STATIC_DRAW);
}
OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
{
    glCreateBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), nullptr, GL_DYNAMIC_DRAW);
}
OpenGLVertexBuffer::OpenGLVertexBuffer(const void* const data, std::size_t size)
{
    glCreateBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
}
OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_renderer_id);
}
void OpenGLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}
void OpenGLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void OpenGLVertexBuffer::setData(const void* data, size_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(size), data);
}
void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
{
    m_layout = layout;
}

OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t>& indicies) : m_renderer_id(0), m_count(static_cast<decltype(m_count)>(indicies.size()))
{
    glCreateBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(uint32_t), indicies.data(), GL_STATIC_DRAW);
}
OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_renderer_id);
}
void OpenGLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}
void OpenGLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

OpenGLVertexArray::OpenGLVertexArray()
{
    m_vertex_buffer_index = 0;
    glCreateVertexArrays(1, &m_renderer_id);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_renderer_id);
}

void OpenGLVertexArray::bind() const
{
    glBindVertexArray(m_renderer_id);
}
void OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}
void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
{
    glBindVertexArray(m_renderer_id);
    buffer->bind();

    const auto& layout = buffer->getLayout();
    for (const auto& element : layout)
    {
        switch (element.type)
        {
            case ShaderUniformType::Float:
            case ShaderUniformType::Float2:
            case ShaderUniformType::Float3:
            case ShaderUniformType::Float4:
            {
                glEnableVertexAttribArray(m_vertex_buffer_index);
                glVertexAttribPointer(m_vertex_buffer_index,
                    static_cast<GLint>(element.getComponentCount()),
                    toOpenGLBaseType(element.type),
                    element.is_normalized ? GL_TRUE : GL_FALSE,
                    static_cast<GLsizei>(layout.getStride()),
                    reinterpret_cast<const void*>(element.offset));
                //(const void*)element.offset);
                // reinterpret_cast<const void*>(element.offset));
                m_vertex_buffer_index++;
                break;
            }
            case ShaderUniformType::Int:
            case ShaderUniformType::Int2:
            case ShaderUniformType::Int3:
            case ShaderUniformType::Int4:
            case ShaderUniformType::Bool:
            {
                glEnableVertexAttribArray(m_vertex_buffer_index);
                glVertexAttribIPointer(m_vertex_buffer_index,
                    static_cast<GLint>(element.getComponentCount()),
                    toOpenGLBaseType(element.type),
                    static_cast<GLsizei>(layout.getStride()),
                    reinterpret_cast<const void*>(element.offset));
                m_vertex_buffer_index++;
                break;
            }
            case ShaderUniformType::UnsignedInt:
            {
                glEnableVertexAttribArray(m_vertex_buffer_index);
                glVertexAttribIPointer(m_vertex_buffer_index,
                    static_cast<GLuint>(element.getComponentCount()),
                    toOpenGLBaseType(element.type),
                    static_cast<GLsizei>(layout.getStride()),
                    reinterpret_cast<const void*>(element.offset));
                m_vertex_buffer_index++;
                break;
            }
            case ShaderUniformType::Mat3:
            case ShaderUniformType::Mat4:
            {
                auto count = element.getComponentCount();
                for (size_t i = 0; i < count; ++i)
                {
                    glEnableVertexAttribArray(m_vertex_buffer_index);
                    glVertexAttribPointer(m_vertex_buffer_index,
                        static_cast<GLint>(count),
                        toOpenGLBaseType(element.type),
                        element.is_normalized ? GL_TRUE : GL_FALSE,
                        static_cast<GLsizei>(layout.getStride()),
                        reinterpret_cast<const void*>(element.offset + sizeof(float) * count * i));
                    glVertexAttribDivisor(m_vertex_buffer_index, 1);
                    m_vertex_buffer_index++;
                }
                break;
            }
            default:
            {
                ME_ENGINE_ERROR("Unsupported shader uniform type {}", static_cast<int>(element.type));
            }
        }
    }
    m_vertex_buffers.push_back(buffer);
}
void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
{
    glBindVertexArray(m_renderer_id);
    buffer->bind();
    m_index_buffer = buffer;
}
}// namespace Meiosis