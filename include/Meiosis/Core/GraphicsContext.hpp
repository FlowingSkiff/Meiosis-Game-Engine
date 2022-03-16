#pragma once
#include "Core.hpp"
#include <memory>
#include "Core.hpp"
namespace Meiosis
{
class ME_API GraphicsContext
{
  public:
    virtual ~GraphicsContext() = default;
    virtual void init() = 0;
    virtual void swapBuffers() = 0;
    static std::unique_ptr<GraphicsContext> create(void* window);
};
}// namespace Meiosis