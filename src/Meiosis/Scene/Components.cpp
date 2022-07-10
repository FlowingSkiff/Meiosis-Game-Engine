#include "Meiosis/Scene/Components.hpp"
#include "Meiosis/Scene/Scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
namespace Meiosis
{
glm::mat4 TransformComponent::getTransform() const
{
    glm::mat4 mat_rot = glm::toMat4(glm::quat(rotation));
    return glm::translate(glm::mat4(1.0f), translation) * mat_rot * glm::scale(glm::mat4(1.0f), scale);
}

MeshComponent::MeshComponent(std::string shader_filename, std::vector<std::string> textures_filenames, std::shared_ptr<VertexArray> vao, Scene* scene) : textures{}, shader{}, vertices{ vao }, m_scene{ scene }
{
    for (const auto& filename : textures_filenames)
    {
        const auto texture = m_scene->loadTexture(filename);
        textures.push_back(texture);
    }
    shader = m_scene->loadShader(shader_filename);
}
}// namespace Meiosis