#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Core/Input.hpp"
#include "Meiosis/Core/Application.hpp"
#include "GLFW/glfw3.h"

namespace Meiosis
{
    namespace Input
    {
        bool isKeyPressed(KeyCode key_code)
        {
            auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
            auto state = glfwGetKey(window, static_cast<int32_t>(key_code));
            return state == GLFW_PRESS || state == GLFW_REPEAT;
        }
        bool isMouseButtonPressed(MouseCode mouse_button)
        {
            auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
            auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouse_button));
            return state == GLFW_PRESS;
        }
        auto getMousePosition() -> glm::vec2
        {
            auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
            double x_pos, y_pos;
            glfwGetCursorPos(window, &x_pos, &y_pos);
            return {static_cast<float>(x_pos), static_cast<float>(y_pos)};
        }
        auto getMouseX() -> float
        {
            return getMousePosition().x;
        }
        auto getMouseY() -> float
        {
            return getMousePosition().y;
        }
    }
}