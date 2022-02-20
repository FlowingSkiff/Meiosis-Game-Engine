#pragma once
#include <vector>
#include <glad/glad.h>
#include <memory>
#include <cassert>
#include <string>

class ComputeShader
{
  public:
    struct ComputeBufferBase
    {
        void* data;
        std::size_t size;
        GLuint renderer_id;
        void bind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, renderer_id); }
        void unbind() const { glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); }
    };

    template<typename Type>
    class ComputeBuffer : public ComputeBufferBase
    {
      public:
        Type* getRawP() { return static_cast<Type*>(this->data); }
        constexpr count() const { return this->size / sizeof(Type); }
    };

    using ComputeObject = std::unique_ptr<ComputeBufferBase>;

  public:
    ComputeShader(const std::string& file_path);
    void compileShader(const std::string& file_path);
    void run();
    template<typename Type>
    ComputeObject generateBufferObject(std::size_t count);

  private:
    std::vector<ComputeObject> m_compute_objects;
    std::size_t m_num_bind_ids = 0u;
    int32_t m_count = -1;
    std::string m_source;
};


template<typename Type>
ComputeShader::ComputeObject ComputeShader::generateBufferObject(std::size_t count)
{
    GLuint tmp_id = m_num_bind_ids++;
    const auto size = count * sizeof(Type);
    glGenBuffers(1, &tmp_id);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, tmp_id);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_STATIC_DRAW);

    Type* buffer = static_cast<Type*>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

    m_compute_objects.push_back(std::make_unique<ComputeBuffer<Type>>(buffer, size, tmp_id));
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    assert(m_count == count || m_count == -1);
    m_count = count;
    return m_compute_objects.back();
}