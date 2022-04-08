#include "Meiosis/Renderer/Shader.hpp"
#include "Meiosis/Renderer/Renderer.hpp"
#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
#include "Meiosis/Core/Log.hpp"
#include <assert.h>
namespace Meiosis
{

void ShaderLibrary::add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    m_shaders[name] = shader;
}
void ShaderLibrary::add(const std::shared_ptr<Shader>& shader)
{
    add(shader->getName(), shader);
}
auto ShaderLibrary::load(const std::string& file_name) -> std::shared_ptr<Shader>
{
    auto shader = Renderer::createShader(file_name);
    add(shader);
    return shader;
}
auto ShaderLibrary::load(const std::string& name, const std::string& file_name) -> std::shared_ptr<Shader>
{
    auto shader = Renderer::createShader(file_name);
    add(name, shader);
    return shader;
}
auto ShaderLibrary::get(const std::string& name) -> std::shared_ptr<Shader>
{
#ifdef ME_DEBUG
    if (!exists(name))
    {
        ME_ENGINE_ERROR("Shader ({}) does not exist", name);
    }
#endif
    return m_shaders[name];
}
bool ShaderLibrary::exists(const std::string& name) const
{
    return m_shaders.find(name) != m_shaders.end();
}
}// namespace Meiosis