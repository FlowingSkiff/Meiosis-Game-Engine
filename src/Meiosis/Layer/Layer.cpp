#include "Layer/Layer.hpp"

namespace Meiosis
{
    Layer::Layer() { }
    Layer::~Layer() { }
    void Layer::onUpdate(float dt) { }
    void Layer::onEvent(Event& e) { }
    void Layer::onAttach() { }
    void Layer::onDetach() { }
}