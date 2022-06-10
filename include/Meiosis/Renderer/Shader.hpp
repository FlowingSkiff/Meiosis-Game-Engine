#pragma once
#include "Meiosis/Core/Core.hpp"
#include <string>
#include <string_view>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
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

class ME_API ShaderLibrary
{
  public:
    using ShaderID = size_t;
    [[nodiscard]] auto add(const std::shared_ptr<Shader>& shader) -> ShaderID;
    [[nodiscard]] auto load(const std::string& file_name) -> ShaderID;
    [[nodiscard]] auto get(ShaderID shader) -> std::shared_ptr<Shader>;
    [[nodiscard]] bool exists(ShaderID id) const;

  private:
    std::vector<std::shared_ptr<Shader>> m_shaders;
};
}// namespace Meiosis
