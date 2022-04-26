#include "Layer/Layer.hpp"

namespace Meiosis
{
Layer::Layer() {}
Layer::~Layer() {}
void Layer::onUpdate([[maybe_unused]] float dt) {}
void Layer::onEvent([[maybe_unused]] Event& e) {}
void Layer::onAttach() {}
void Layer::onDetach() {}
void Layer::onImguiRender() {}
}// namespace Meiosis