#include "Meiosis/Renderer/Material.hpp"

namespace Meiosis
{
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