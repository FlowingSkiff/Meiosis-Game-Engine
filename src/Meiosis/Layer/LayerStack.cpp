#include "Meiosis/Layer/LayerStack.hpp"
#include "Meiosis/Core/Log.hpp"
#include <iterator>
namespace Meiosis
{
LayerStack::LayerStack() {}
LayerStack::~LayerStack()
{
    clear();
}

LayerStack::LayerStack(LayerStack&& stack) noexcept
{
    m_layers = stack.m_layers;
    m_overlay_count = stack.m_overlay_count;

    stack.detach();
}

LayerStack& LayerStack::operator=(LayerStack&& stack) noexcept
{
    this->clear();
    m_layers = stack.m_layers;
    m_overlay_count = stack.m_overlay_count;
    stack.detach();
    return *this;
}

void LayerStack::clear()
{
    for (auto layer_ptr : m_layers)
        delete layer_ptr;
    m_overlay_count = 0;
}
void LayerStack::detach()
{
    m_overlay_count = 0;
    m_layers.clear();
}

void LayerStack::pushOverlay(Layer* layer)
{
    m_layers.push_back(layer);
    m_overlay_count++;
}
void LayerStack::pushLayer(Layer* layer)
{
    const auto ins_index = m_layers.size() - m_overlay_count;
#ifdef ME_DEBUG
    if (ins_index >= m_layers.size())
    {
        ME_ENGINE_ERROR("Overlay count ({}) is greater than the total amount of layers ({}).", m_overlay_count, m_layers.size());
        return;
    }
#endif
    auto ins_iter = m_layers.begin();
    std::advance(ins_iter, ins_index);
    m_layers.insert(ins_iter, layer);
}

void LayerStack::detachLayer(Layer* layer)
{
    for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
    {
        if (*it == layer)
        {
            m_layers.erase(it);
            break;
        }
    }
}
void LayerStack::deleteLayer(Layer* layer)
{
    detachLayer(layer);
    delete layer;
}

}// namespace Meiosis