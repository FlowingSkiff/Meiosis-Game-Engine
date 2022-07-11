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
auto ShaderLibrary::loadShader(const std::string& file_name) -> ShaderID
{
    return add(Renderer::createShader(file_name));
}
auto ShaderLibrary::getShader(ShaderID id) -> std::shared_ptr<Shader>
{
    return m_shaders.at(id);
}
bool ShaderLibrary::exists(ShaderID id) const
{
    return m_shaders.size() > id;
}

auto ShaderLibrary::add(const Material& material) -> MaterialID
{
    m_materials.push_back(material);
    return m_materials.size() - 1;
}
auto ShaderLibrary::loadMaterial(const std::string& file_name, Material::UniformFunction op) -> MaterialID
{
    auto shader = Renderer::createShader(file_name);
    return add(Renderer::createMaterial(shader, op));
}
auto ShaderLibrary::getMaterial(MaterialID material) -> Material&
{
    return m_materials.at(material);
}
bool ShaderLibrary::materialExists(MaterialID material) const
{
    return m_materials.size() > material;
}

Material::Material(std::shared_ptr<Shader>& shader) : m_shader(shader) {}
Material::Material(std::shared_ptr<Shader>&& shader) : m_shader(shader) {}
Material::Material(std::shared_ptr<Shader>& shader, UniformFunction function) : m_shader(shader), m_uniform_function(function) {}
void Material::setOnBind(UniformFunction function)
{
    m_uniform_function = function;
}
auto Material::getShader() -> std::shared_ptr<Shader>
{
    if (m_uniform_function)
    {
        m_shader->bind();
        m_uniform_function(m_shader);
    }
    return m_shader;
}
}// namespace Meiosis