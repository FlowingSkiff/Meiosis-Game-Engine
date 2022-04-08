#pragma once
#include "Meiosis/Core/Core.hpp"
#include <glm/glm.hpp>
namespace Meiosis
{
class ME_API Camera
{
  public:
    virtual ~Camera() = default;
    virtual auto getViewProjectionMatrix() const -> const glm::mat4& = 0;
};
}// namespace Meiosis