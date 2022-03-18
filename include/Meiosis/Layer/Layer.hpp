#pragma once
#include "../Core/Core.hpp"
#include "../Events/Event.hpp"
namespace Meiosis
{
class ME_API Layer
{
  public:
    Layer();
    virtual ~Layer();
    virtual void onUpdate(float dt);
    virtual void onEvent(Event& e);
    virtual void onAttach();
    virtual void onDetach();
};
}// namespace Meiosis