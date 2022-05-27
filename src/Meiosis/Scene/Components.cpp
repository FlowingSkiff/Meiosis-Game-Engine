#include "Meiosis/Scene/Components.hpp"
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
}// namespace Meiosis