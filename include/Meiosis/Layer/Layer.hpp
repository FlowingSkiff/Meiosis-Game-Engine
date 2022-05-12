#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Events/Event.hpp"
#include "Meiosis/Core/Timestep.hpp"
namespace Meiosis
{
class ME_API Layer
{
  public:
    Layer();
    virtual ~Layer();
    virtual void onUpdate(Timestep dt);
    virtual void onEvent(Event& e);
    virtual void onAttach();
    virtual void onDetach();
    virtual void onImguiRender();
};
}// namespace Meiosis