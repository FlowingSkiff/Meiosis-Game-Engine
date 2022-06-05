#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/Shader.hpp"
#include <functional>

namespace Meiosis
{
class ME_API Material
{
  public:
    using UniformFunction = std::function<void(std::shared_ptr<Shader>&)>;
    Material() = default;
    explicit Material(std::shared_ptr<Shader>& shader);
    explicit Material(std::shared_ptr<Shader>&& shader);

    Material(const Material& other) = default;
    Material(Material&& other) = default;

    Material& operator=(const Material& other) = default;
    Material& operator=(Material&& other) = default;

    ~Material() = default;
    
    Material(std::shared_ptr<Shader>& shader, UniformFunction fn);
    void setOnBind(UniformFunction fn);
    [[nodiscard]] auto getShader() -> std::shared_ptr<Shader>;

  private:
    std::shared_ptr<Shader> m_shader;
    UniformFunction m_uniform_function;
};
}// namespace Meiosis