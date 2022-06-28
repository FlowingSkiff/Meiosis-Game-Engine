#pragma once
#include "Meiosis/Core/Core.hpp"
#include <string>
#include "Meiosis/Scene/SceneCamera.hpp"
#include <glm/glm.hpp>
#include "Meiosis/Renderer/RendererBuffer.hpp"
#include "Meiosis/Renderer/Shader.hpp"
#include "Meiosis/Renderer/Texture.hpp"
#include <vector>
namespace Meiosis
{
struct TransformComponent
{
    glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    [[nodiscard]] glm::mat4 getTransform() const;
};
struct TagComponent
{
    std::string tag = "";
};
struct CameraComponent
{
    bool is_primary = false;
    bool has_fixed_aspect_ratio = false;
    SceneCamera camera;
};

struct MeshComponent
{
    MeshComponent(std::vector<TextureLibrary::TextureID>&& texts, ShaderLibrary::ShaderID&& shader_id, std::shared_ptr<VertexArray>&& vao):
        textures{texts}, shader{shader_id}, vertices{vao} { }
    std::vector<TextureLibrary::TextureID> textures;
    ShaderLibrary::ShaderID shader;
    std::shared_ptr<VertexArray> vertices;
};
}// namespace Meiosis