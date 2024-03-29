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
class Scene;
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
    MeshComponent(std::string shader_filename, std::vector<std::string> textures_filenames, std::shared_ptr<VertexArray> vao, Scene* scene);
    MeshComponent(std::string shader_filename, Material::UniformFunction op, std::vector<std::string> textures_filenames, std::shared_ptr<VertexArray> vao, Scene* scene);
    std::vector<TextureLibrary::TextureID> textures;
    ShaderLibrary::ShaderID shader;
    std::shared_ptr<VertexArray> vertices;
    ShaderLibrary::MaterialID material;
    bool is_material = false;

    auto getShader() -> std::shared_ptr<Shader>;
    auto getTexture(TextureLibrary::TextureID id) -> std::shared_ptr<Texture>;// TODO: check if it owns the texture

  private:
    Scene* m_scene = nullptr;
};
}// namespace Meiosis