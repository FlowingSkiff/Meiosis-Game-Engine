#include "Meiosis/Core/Core.hpp"
#include <glm/glm.hpp>
namespace Meiosis
{
class ME_API Camera2D
{
  public:
    Camera2D(float left, float right, float bottom, float top);
    virtual ~Camera2D() = default;

  public:
    auto getProjectionMatrix() const -> const glm::mat4&;
    auto getViewMatrix() const -> const glm::mat4&;
    auto getViewProjectionMatrix() const -> const glm::mat4&;
    auto getPosition() const -> const glm::vec3&;
    auto getRotation() const -> float;

  public:
    void setProjectionMatrix(const glm::mat4& proj);
    void setProjectionMatrix(float left, float right, float bottom, float top);
    void setPosition(const glm::vec3& proj);
    void setRotation(float rot);

  protected:
    void recalculateViewMatrix();

  protected:
    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;
    glm::mat4 m_view_projection_matrix;
    glm::vec3 m_position;
    float m_rotation;
};
}// namespace Meiosis