#pragma once
#include "Core.hpp"
#include <memory>
namespace Meiosis
{
class ME_API GraphicsContext
{
  public:
    explicit GraphicsContext() = default;
    virtual ~GraphicsContext() = default;
    GraphicsContext(const GraphicsContext&) = default;
    GraphicsContext(GraphicsContext&&) = default;
    GraphicsContext& operator=(const GraphicsContext&) = default;
    GraphicsContext& operator=(GraphicsContext&&) = default;
    virtual void init() = 0;
    virtual void swapBuffers() = 0;
    static std::unique_ptr<GraphicsContext> create(void* window);
};
}// namespace Meiosis