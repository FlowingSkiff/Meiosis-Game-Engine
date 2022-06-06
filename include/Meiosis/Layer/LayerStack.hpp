#pragma once
#include "../Core/Core.hpp"
#include "Layer.hpp"
#include <vector>
#include <cstdint>
namespace Meiosis
{
class ME_API LayerStack
{
  public:
    LayerStack();
    ~LayerStack();
    // Non copiable, does not make sense
    LayerStack(const LayerStack&) = delete;
    LayerStack& operator=(const LayerStack&) = delete;
    // move into new, does not delete
    LayerStack(LayerStack&&) noexcept;
    LayerStack& operator=(LayerStack&&) noexcept;

  private:
    // Removes layers but does not delete them
    void detach();
    // Deletes all layers
    void clear();

  public:// Iterators
    auto begin() { return m_layers.begin(); }
    auto end() { return m_layers.end(); }
    auto begin() const { return m_layers.begin(); }
    auto end() const { return m_layers.end(); }
    auto rbegin() { return m_layers.rbegin(); }
    auto rend() { return m_layers.rend(); }
    auto rbegin() const { return m_layers.rbegin(); }
    auto rend() const { return m_layers.rend(); }

  public:// Add or remove layers to stack
    void pushOverlay(Layer*);
    void pushLayer(Layer*);
    // removes, but does not delete
    void detachLayer(Layer*);
    // removes and deletes layer
    void deleteLayer(Layer*);

  private:
    std::vector<Layer*> m_layers;
    uint16_t m_overlay_count = 0U;
};
}// namespace Meiosis