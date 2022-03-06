#pragma once

#include "../../Core/Core.hpp"
#include "../../Core/GraphicsContext.hpp"
struct GLFWwindow;

namespace Meiosis
{
class ME_API OpenGLGraphicsContext : public GraphicsContext
{
  public:
    OpenGLGraphicsContext(GLFWwindow* window);
    virtual void init() override;
    virtual void swapBuffers() override;

  private:
    GLFWwindow* m_window = nullptr;
};
}// namespace Meiosis