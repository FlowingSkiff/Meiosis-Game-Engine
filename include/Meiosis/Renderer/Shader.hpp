#pragma once
#include "Meiosis/Core/Core.hpp"
#include <string>
#include <unordered_map>
#include <string_view>
#include <glm/glm.hpp>
#include <memory>
namespace Meiosis
{
class ME_API Shader
{
  public:
    virtual ~Shader() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setInt(const std::string& name, int value) = 0;
    virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
    virtual void setFloat(const std::string& name, float value) = 0;
    virtual void setFloat2(const std::string& name, const glm::vec2& value) = 0;
    virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
    virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;

    virtual const std::string& getName() const = 0;
};

class ME_API ShaderLibrary
{
  public:
    void add(const std::string& name, const std::shared_ptr<Shader>& shader);
    void add(const std::shared_ptr<Shader>& shader);
    auto load(const std::string& file_name) -> std::shared_ptr<Shader>;
    auto load(const std::string& name, const std::string& file_name) -> std::shared_ptr<Shader>;
    auto get(const std::string& name) -> std::shared_ptr<Shader>;
    bool exists(const std::string& name) const;

  private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
};
}// namespace Meiosis
