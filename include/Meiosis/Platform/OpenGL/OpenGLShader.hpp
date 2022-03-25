#pragma once

#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/Shader.hpp"
#include <glad/glad.h>

namespace Meiosis
{
    class ME_API OpenGLShader : public Shader
    {
        public:
            using source_map = std::unordered_map<GLenum, std::string>;
        public:
            OpenGLShader::OpenGLShader(const std::string& file_path);
            OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);
            virtual ~OpenGLShader();
            virtual void bind() const override;
            virtual void unbind() const override;
            virtual void setInt(const std::string& name, int value) override;
            virtual void setIntArray(const std::string& name, int* values, uint32_t count) override;
            virtual void setFloat(const std::string& name, float value) override;
            virtual void setFloat2(const std::string& name, const glm::vec2& value) override;
            virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
            virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
            virtual void setMat4(const std::string& name, const glm::mat4& value) override;

        public:
            void uploadUniform(const std::string& name, int value);
            void uploadUniform(const std::string& name, int* values, uint32_t count);
            void uploadUniform(const std::string& name, float value);
            void uploadUniform(const std::string& name, const glm::vec2& value);
            void uploadUniform(const std::string& name, const glm::vec3& value);
            void uploadUniform(const std::string& name, const glm::vec4& value);
            void uploadUniform(const std::string& name, const glm::mat3& mat);
            void uploadUniform(const std::string& name, const glm::mat4& mat);
        private:
            void generate(source_map& sources);
            
        private:
            uint32_t m_renderer_id;
            std::string m_file_path;
            std::string m_name;
    };
}