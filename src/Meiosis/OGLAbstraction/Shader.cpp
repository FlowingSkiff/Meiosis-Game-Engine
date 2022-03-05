#include "OGLAbstraction/Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "OGLAbstraction/Renderer.hpp"
#include "Core/Log/Log.hpp"
Shader::Shader(const std::string& name) : m_RendererID(0)
{
    auto shader = ParseShader(name);
    m_RendererID = CreateShader(shader);
}


Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

unsigned int Shader::CreateShader(const ShaderProgramSource& shader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, shader.vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shader.fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);


    return program;
}

Shader::ShaderProgramSource Shader::ParseShader(const std::string& filepath) const
{
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    std::ifstream ifile(filepath);
    std::string line;
    std::ostringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(ifile, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        char buffer[512];
        int length;
        glGetShaderInfoLog(id, 512, &length, buffer);
        ENGINE_ERROR("Shader could not be compiled. Returned error code {}", buffer);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}
void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 v)
{
    glUniform4f(GetUniformLocation(name), v[0], v[1], v[2], v[3]);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    return glGetUniformLocation(m_RendererID, name.c_str());
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat<4, 4, float>& m)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}