#pragma once
#include "../Core/Core.hpp"
#include <string>
#include "Meiosis/Scene/SceneCamera.hpp"
#include <glm/glm.hpp>
namespace Meiosis
{
struct TransformComponent
{
    glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    glm::mat4 getTransform() const;
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
}// namespace Meiosis