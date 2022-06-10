#include "Meiosis/Renderer/Shader.hpp"
#include "Meiosis/Renderer/Renderer.hpp"
#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
#include "Meiosis/Core/Log.hpp"
#include <assert.h>
namespace Meiosis
{

auto ShaderLibrary::add(const std::shared_ptr<Shader>& shader) -> ShaderID
{
    m_shaders.push_back(shader);
    return m_shaders.size() - 1;
}
auto ShaderLibrary::load(const std::string& file_name) -> ShaderID
{
    return add(Renderer::createShader(file_name));
}
auto ShaderLibrary::get(ShaderID id) -> std::shared_ptr<Shader>
{
    return m_shaders.at(id);
}
bool ShaderLibrary::exists(ShaderID id) const
{
    return m_shaders.size() > id;
}
}// namespace Meiosis