#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/Camera.hpp"
namespace Meiosis
{
class SceneCamera : public Camera
{
  public:
    SceneCamera();
    SceneCamera(const SceneCamera&) = default;
    SceneCamera(SceneCamera&&) = default;
    SceneCamera& operator=(const SceneCamera&) = default;
    SceneCamera& operator=(SceneCamera&&) = default;
    virtual ~SceneCamera() = default;
    virtual auto getViewProjectionMatrix() const -> const glm::mat4& override;
    void setViewportSize(uint32_t width, uint32_t height);

  private:
    void recalculateViewProjectionMatrix();
    float m_aspect_ratio = 0.0f;
    float m_orthographic_size = 10.0f;
    float m_orthographic_near = -1.0f;
    float m_orthographic_far = 1.0f;
    glm::mat4 m_projection_matrix = glm::mat4(1.0f);
};
}// namespace Meiosis