#include "Meiosis/Scene/SceneCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace Meiosis
{
SceneCamera::SceneCamera()
{
    recalculateViewProjectionMatrix();
}
auto SceneCamera::getViewProjectionMatrix() const -> const glm::mat4&
{
    return m_projection_matrix;
}
void SceneCamera::setViewportSize(uint32_t width, uint32_t height)
{
    m_aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    recalculateViewProjectionMatrix();
}
void SceneCamera::recalculateViewProjectionMatrix()
{
    float ortho_left = -m_orthographic_size * m_aspect_ratio * 0.5f;
    float ortho_right = m_orthographic_size * m_aspect_ratio * 0.5f;
    float ortho_bottom = -m_orthographic_size * 0.5f;
    float ortho_top = m_orthographic_size * 0.5f;
    m_projection_matrix = glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top, m_orthographic_near, m_orthographic_far);
}
}// namespace Meiosis