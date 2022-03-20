#pragma once

#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Layer/Layer.hpp"
#include "Meiosis/Events/Event.hpp"

namespace Meiosis
{
class ME_API ImguiLayer : public Layer
{
  public:
    ImguiLayer();
    virtual ~ImguiLayer() = default;
    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onEvent(Event& e) override;

    void beginFrame();
    void endFrame();

    void blockEvents(bool should_block) { m_block_events = should_block; }

    void setDarkThemeColors();

  private:
    bool m_block_events = true;
};
}// namespace Meiosis