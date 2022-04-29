#pragma once
#include "Meiosis/Core/Core.hpp"

namespace Meiosis
{
class ME_API Texture
{
  public:
    virtual ~Texture() = default;
    virtual auto getWidth() const -> uint32_t = 0;
    virtual auto getHeight() const -> uint32_t = 0;
    virtual auto getRendererID() const -> uint32_t = 0;

    virtual void setData(void* data, uint32_t size) = 0;
    virtual void bind(uint32_t slot = 0) const = 0;
    virtual bool isLoaded() const = 0;
    virtual bool operator==(const Texture& other) const = 0;
};
}// namespace Meiosis