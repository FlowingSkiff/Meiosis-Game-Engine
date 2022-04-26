#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include "Meiosis/Util/FileUtils.hpp"
#include <fstream>
#include "Meiosis/Core/Log.hpp"
namespace Meiosis
{
namespace details
{
    auto readFile(const std::string& file_path) -> std::string
    {
        std::string source;
        std::ifstream file(file_path, std::ios::in | std::ios::binary);
        if (!file.is_open())
        {
            ME_ENGINE_ERROR("Coule not open file: {}", file_path);
            return "";
        }
        file.seekg(0, std::ios::end);
        auto size = file.tellg();
        if (file.fail())
        {
            ME_ENGINE_ERROR("Could not read from file: {}", file_path);
        }
        source.resize(static_cast<size_t>(size));
        file.seekg(0, std::ios::beg);
        file.read(source.data(), size);
        return source;
    }
    auto splitSource(const std::string& source) -> OpenGLShader::source_map
    {
        // Shaders are in the form of #shader-type VERTEX ... #shader-type FRAGMENT
        OpenGLShader::source_map sources;
        const std::string vertex_str{ "#shader-type VERTEX" };
        const std::string fragment_str{ "#shader-type FRAGMENT" };
        const auto vertex_begin = source.find(vertex_str);
        const auto fragment_begin = source.find(fragment_str);
        if (vertex_begin != std::string::npos && fragment_begin != std::string::npos)
        {
            if (vertex_begin < fragment_begin)
            {
                const auto vertex_offset = vertex_begin + vertex_str.size();
                sources[GL_VERTEX_SHADER] = source.substr(vertex_offset, fragment_begin - vertex_offset);
                sources[GL_FRAGMENT_SHADER] = source.substr(fragment_begin + fragment_str.size());
            }
            else
            {
                const auto fragment_offset = fragment_begin + fragment_str.size();
                sources[GL_FRAGMENT_SHADER] = source.substr(fragment_offset, vertex_begin - fragment_offset);
                sources[GL_VERTEX_SHADER] = source.substr(vertex_begin + vertex_str.size());
            }
        }
        else
        {
            ME_ENGINE_ERROR("Error loading shader, vertex({}) and fragment({}) shaders not found.", vertex_begin, fragment_begin);
        }
        return sources;
    }
}// namespace details
OpenGLShader::OpenGLShader(const std::string& file_path) : m_file_path(file_path)
{
    std::string source = details::readFile(file_path);
    auto shader_sources = details::splitSource(source);
    generate(shader_sources);
    m_name = Util::filenameFromPath(file_path, true);
}
OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source) : m_file_path(), m_name(name)
{
    source_map sources;
    sources[GL_VERTEX_SHADER] = vertex_source;
    sources[GL_FRAGMENT_SHADER] = fragment_source;
    generate(sources);
}

void OpenGLShader::generate(source_map& sources)
{
    auto program = glCreateProgram();
    auto vs = CompileShaderFromSource(GL_VERTEX_SHADER, sources[GL_VERTEX_SHADER]);
    auto fs = CompileShaderFromSource(GL_FRAGMENT_SHADER, sources[GL_FRAGMENT_SHADER]);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    m_renderer_id = program;
}

uint16_t OpenGLShader::CompileShaderFromSource(uint16_t type, const std::string& source)
{
    auto id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        char error_buffer[512];
        int length;
        glGetShaderInfoLog(id, 512, &length, error_buffer);
        ME_ENGINE_ERROR("Could not compile {} shader", type);
        ME_ENGINE_ERROR("Shader compile error: {}", error_buffer);
        glDeleteShader(id);
    }
    return static_cast<uint16_t>(id);
}
OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_renderer_id);
}
void OpenGLShader::bind() const
{
    glUseProgram(m_renderer_id);
}
void OpenGLShader::unbind() const
{
    glUseProgram(0);
}
void OpenGLShader::setInt(const std::string& name, int value)
{
    uploadUniform(name, value);
}
void OpenGLShader::setIntArray(const std::string& name, int* values, uint32_t count)
{
    uploadUniform(name, values, count);
}
void OpenGLShader::setFloat(const std::string& name, float value)
{
    uploadUniform(name, value);
}
void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& value)
{
    uploadUniform(name, value);
}
void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value)
{
    uploadUniform(name, value);
}
void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value)
{
    uploadUniform(name, value);
}
void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value)
{
    uploadUniform(name, value);
}

void OpenGLShader::uploadUniform(const std::string& name, int value)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform1i(location, value);
}
void OpenGLShader::uploadUniform(const std::string& name, int* values, uint32_t count)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform1iv(location, static_cast<GLsizei>(count), values);
}
void OpenGLShader::uploadUniform(const std::string& name, float value)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform1f(location, value);
}
void OpenGLShader::uploadUniform(const std::string& name, const glm::vec2& value)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform2f(location, value.x, value.y);
}
void OpenGLShader::uploadUniform(const std::string& name, const glm::vec3& value)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}
void OpenGLShader::uploadUniform(const std::string& name, const glm::vec4& value)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}
void OpenGLShader::uploadUniform(const std::string& name, const glm::mat3& mat)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
void OpenGLShader::uploadUniform(const std::string& name, const glm::mat4& mat)
{
    const GLint location = glGetUniformLocation(m_renderer_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}
auto OpenGLShader::getName() const -> const std::string&
{
    return m_name;
}
}// namespace Meiosis