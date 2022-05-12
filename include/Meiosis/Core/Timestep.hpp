#pragma once
#include "Meiosis/Core/Core.hpp"

namespace Meiosis
{
class ME_API Timestep
{
  public:
    Timestep(float time = 0.0f) : m_time(time) {}
    operator float() const
    {
        return m_time;
    }
    auto getSeconds() const
    {
        return m_time;
    }
    auto getMilliseconds() const
    {
        return m_time * 1000.0f;
    }

  private:
    float m_time;
};
}// namespace Meiosis