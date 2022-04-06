#include "Meiosis/Renderer/Camera2D.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace Meiosis
{
// clang-format off
Camera2D::Camera2D( float left, float right, 
                    float bottom, float top) : 
                    m_projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
                    m_view_matrix(1.0f),
                    m_view_projection_matrix(m_projection_matrix * m_view_matrix), 
                    m_position{0.f, 0.f, 0.f},
                    m_rotation{ 0 }
{
}
// clang-format on
auto Camera2D::getProjectionMatrix() const -> const glm::mat4&
{
    return m_projection_matrix;
}

auto Camera2D::getViewMatrix() const -> const glm::mat4&
{
    return m_view_matrix;
}

auto Camera2D::getViewProjectionMatrix() const -> const glm::mat4&
{
    return m_view_projection_matrix;
}

auto Camera2D::getPosition() const -> const glm::vec3&
{
    return m_position;
}

auto Camera2D::getRotation() const -> float
{
    return m_rotation;
}

void Camera2D::setProjectionMatrix(const glm::mat4& proj)
{
    m_projection_matrix = proj;
}

void Camera2D::setProjectionMatrix(float left, float right, float bottom, float top)
{
    m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void Camera2D::setPosition(const glm::vec3& pos)
{
    m_position = pos;
    recalculateViewMatrix();
}

void Camera2D::setRotation(float rot)
{
    m_rotation = rot;
    recalculateViewMatrix();
}

void Camera2D::recalculateViewMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

    m_view_matrix = glm::inverse(transform);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}


}// namespace Meiosis