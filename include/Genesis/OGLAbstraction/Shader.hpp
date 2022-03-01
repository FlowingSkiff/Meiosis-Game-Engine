#pragma once
#include <string>
#include "glm\glm.hpp"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\gtc\matrix_transform.hpp"
class Shader
{
public:
    Shader(const std::string& filename);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, glm::vec4 v);
    void SetUniformMat4f(const std::string& name, const glm::mat<4, 4, float>& m);
    unsigned int GetUniformLocation(const std::string& name);
private:
    struct ShaderProgramSource
    {
        std::string vertexSource;
        std::string fragmentSource;
    };
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const ShaderProgramSource&);
    ShaderProgramSource ParseShader(const std::string& name) const;
private:
    unsigned int m_RendererID;
};