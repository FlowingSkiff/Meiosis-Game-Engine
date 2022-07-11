#pragma once
#include "Meiosis/Core/Core.hpp"
#include <string>
#include <string_view>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <functional>
namespace Meiosis
{
class ME_API Shader
{
  public:
    virtual ~Shader() = default;
    explicit Shader() = default;
    Shader(const Shader&) = default;
    Shader(Shader&&) = default;
    Shader& operator=(const Shader&) = default;
    Shader& operator=(Shader&&) = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
    virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;

    [[nodiscard]] virtual const std::string& getName() const = 0;
};

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
class ME_API ShaderLibrary
{
  public:
    using ShaderID = size_t;
    using MaterialID = size_t;
    [[nodiscard]] auto add(const std::shared_ptr<Shader>& shader) -> ShaderID;
    [[nodiscard]] auto loadShader(const std::string& file_name) -> ShaderID;
    [[nodiscard]] auto getShader(ShaderID shader) -> std::shared_ptr<Shader>;
    [[nodiscard]] bool exists(ShaderID id) const;
    [[nodiscard]] auto add(const Material& material) -> MaterialID;
    [[nodiscard]] auto loadMaterial(const std::string& file_name, Material::UniformFunction op) -> MaterialID;
    [[nodiscard]] auto getMaterial(MaterialID material) -> Material&;
    [[nodiscard]] bool materialExists(MaterialID material) const;

  private:
    std::vector<std::shared_ptr<Shader>> m_shaders;
    std::vector<Material> m_materials;
};
}// namespace Meiosis
