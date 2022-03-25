#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Core/KeyCodes.hpp"
#include "Meiosis/Core/MouseCodes.hpp"
#include <glm/glm.hpp>

namespace Meiosis
{
    namespace Input
    {
        bool isKeyPressed(KeyCode key_code);
        bool isMouseButtonPressed(MouseCode mouse_button);
        auto getMousePosition() -> glm::vec2;
        auto getMouseX() -> float;
        auto getMouseY() -> float;
    }
}