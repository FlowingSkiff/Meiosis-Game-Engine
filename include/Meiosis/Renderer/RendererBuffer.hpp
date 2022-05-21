#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Core/Log.hpp"
#include <memory>
#include <string>
#include <vector>
namespace Meiosis
{
enum class ShaderUniformType : uint8_t {
    None = 0u,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool,
    UnsignedInt
};

static constexpr size_t shaderUniformTypeSize(ShaderUniformType type)
{
    switch (type)
    {
        case ShaderUniformType::None:
            return 0;
            break;
        case ShaderUniformType::Float:
            return sizeof(float);
            break;
        case ShaderUniformType::Float2:
            return 2 * sizeof(float);
            break;
        case ShaderUniformType::Float3:
            return 3 * sizeof(float);
            break;
        case ShaderUniformType::Float4:
            return 4 * sizeof(float);
            break;
        case ShaderUniformType::Mat3:
            return 3 * 3 * sizeof(float);
            break;
        case ShaderUniformType::Mat4:
            return 4 * 4 * sizeof(float);
            break;
        case ShaderUniformType::Int:
            return sizeof(int);
            break;
        case ShaderUniformType::Int2:
            return 2 * sizeof(int);
            break;
        case ShaderUniformType::Int3:
            return 3 * sizeof(int);
            break;
        case ShaderUniformType::Int4:
            return 4 * sizeof(int);
            break;
        case ShaderUniformType::Bool:
            return sizeof(bool);
            break;
        case ShaderUniformType::UnsignedInt:
            return sizeof(unsigned int);
            break;
    }
    ME_ENGINE_ERROR("Unknown uniform type: {}", static_cast<int>(type));
    return 0;
}

struct BufferObject
{
    std::string name;
    ShaderUniformType type = ShaderUniformType::None;
    size_t size = 0U;
    size_t offset = 0U;
    bool is_normalized = false;

    BufferObject() = default;
    BufferObject(std::string iname, ShaderUniformType itype, bool inormalized = false) : name(std::move(iname)), type(itype), size(shaderUniformTypeSize(type)), is_normalized(inormalized)
    {
    }

    [[nodiscard]] size_t getComponentCount() const
    {
        switch (type)
        {
            case ShaderUniformType::None:
                return 0;
                break;
            case ShaderUniformType::Float:
                return 1;
                break;
            case ShaderUniformType::Float2:
                return 2;
                break;
            case ShaderUniformType::Float3:
                return 3;
                break;
            case ShaderUniformType::Float4:
                return 4;
                break;
            case ShaderUniformType::Mat3:
                return 3;
                break;
            case ShaderUniformType::Mat4:
                return 4;
                break;
            case ShaderUniformType::Int:
                return 1;
                break;
            case ShaderUniformType::Int2:
                return 2;
                break;
            case ShaderUniformType::Int3:
                return 3;
                break;
            case ShaderUniformType::Int4:
                return 4;
                break;
            case ShaderUniformType::Bool:
                return 1;
                break;
            case ShaderUniformType::UnsignedInt:
                return 1;
                break;
        }
        return 0;
    }
};

class ME_API BufferLayout
{
  public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferObject> elements);
    [[nodiscard]] auto getStride() const { return m_stride; }
    [[nodiscard]] auto getElements() const { return m_elements; }
    [[nodiscard]] auto begin() { return m_elements.begin(); }
    [[nodiscard]] auto end() { return m_elements.end(); }
    [[nodiscard]] auto begin() const { return m_elements.begin(); }
    [[nodiscard]] auto end() const { return m_elements.end(); }

  private:
    void calculateOffsetAndStride();

  private:
    std::vector<BufferObject> m_elements;
    size_t m_stride;
};

class ME_API VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setData(const void* data, size_t size) = 0;
    [[nodiscard]] virtual auto getLayout() const -> const BufferLayout& = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;

  private:
};

class ME_API IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    [[nodiscard]] virtual auto getCount() const -> uint32_t = 0;
};

class ME_API VertexArray
{
  public:
    virtual ~VertexArray() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

    [[nodiscard]] virtual auto getVertexBuffers() const -> const std::vector<std::shared_ptr<VertexBuffer>>& = 0;
    [[nodiscard]] virtual auto getIndexBuffer() const -> const std::shared_ptr<IndexBuffer>& = 0;
};
}// namespace Meiosis