#pragma once
#include "Meiosis/Core/Core.hpp"

namespace Meiosis
{
class ME_API Timestep
{
  public:
    Timestep(float time = 0.0F) : m_time(time) {}
    operator float() const
    {
        return m_time;
    }
    [[nodiscard]] auto getSeconds() const
    {
        return m_time;
    }
    [[nodiscard]] auto getMilliseconds() const
    {
        return m_time * 1000.0F;
    }

  private:
    float m_time;
};
}// namespace Meiosis