#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Core/Timestep.hpp"
#include <entt/entt.hpp>
#include <utility>
namespace Meiosis
{
class Entity;
class ME_API Scene
{
  public:
    Scene();
    ~Scene();
    Entity createEntity(const std::string& name = std::string());
    void deleteEntity(Entity entity);
    void onUpdate(Timestep ts);
    void onEditorUpdate(Timestep ts /*, Camera& camera */);
    Entity getCameraEntity();

    void onViewportResize(uint32_t width, uint32_t height);

    template<typename Component>
    void onComponentAdded(uint32_t entity_id, Component component);
    template<typename Component, typename... ARGS>
    auto addComponentTo(Entity entity_id, ARGS... args) -> Component&;
    template<typename Component>
    auto getComponentFrom(Entity entity_id) -> Component&;
    template<typename Component>
    [[nodiscard]] bool entityHas(Entity entity_id) const;
    template<typename Component>
    void removeComponentFrom(Entity entity_id);

  private:
    entt::registry m_registry;
    uint32_t m_view_width = 0U;
    uint32_t m_view_height = 0U;
};

template<typename Component, typename... ARGS>
auto Scene::addComponentTo(Entity entity_id, ARGS... args) -> Component&
{
    return m_registry.emplace<Component>(entity_id, std::forward<ARGS>(args)...);
}
template<typename Component>
auto Scene::getComponentFrom(Entity entity_id) -> Component&
{
    return m_registry.get<Component>(entity_id);
}
template<typename Component>
bool Scene::entityHas(Entity entity_id) const
{
    return m_registry.any_of<Component>(entity_id);
}
template<typename Component>
void Scene::removeComponentFrom(Entity entity_id)
{
    m_registry.remove<Component>(entity_id);
}


}// namespace Meiosis