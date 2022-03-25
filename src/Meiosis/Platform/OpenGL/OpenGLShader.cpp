#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <Meiosis/Util/FileUtils.hpp>
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
            size_t size = file.tellg();
            if (size == -1)
            {
                ME_ENGINE_ERROR("Could not read from file: {}", file_path);
            }
            source.resize(size);
            file.seekg(0, std::ios::beg);
            file.read(source.data(), size);
            return source;
        }
        // TODO: HERE
        auto splitSource(const std::string& source) -> OpenGLShader::source_map
        {
            OpenGLShader::source_map sources;
            return sources;
        }
    }
    OpenGLShader::OpenGLShader(const std::string& file_path):
        m_file_path(file_path)
    {
        std::string source = details::readFile(file_path);
        auto shader_sources = details::splitSource(source);
        generate(shader_sources);
        m_name = Util::filenameFromPath(file_path, true);
    }
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source):
        m_file_path(), m_name(name)
    {
        source_map sources;
        sources[GL_VERTEX_SHADER] = vertex_source;
        sources[GL_FRAGMENT_SHADER] = fragment_source;
        generate(sources);
    }
    // TODO: here
    void OpenGLShader::generate(source_map& souces)
    {

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
        glUniform1iv(location, count, values);
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
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}