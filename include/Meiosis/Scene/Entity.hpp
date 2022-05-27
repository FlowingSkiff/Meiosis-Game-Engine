#pragma once
#include "Meiosis/Core/Core.hpp"
#include <entt/entt.hpp>
#include "Meiosis/Scene/Scene.hpp"
namespace Meiosis
{
class ME_API Entity
{
  public:
    Entity() = default;
    explicit Entity(entt::entity id);
    Entity(entt::entity id, Scene* scene);

    Entity(const Entity&) = default;
    Entity(Entity&&) = default;
    Entity& operator=(const Entity&) = default;
    Entity& operator=(Entity&&) = default;
    ~Entity() = default;

    void setScene(Scene* scene);

    template<typename Component, typename... ARGS>
    auto addComponent(ARGS... args) -> Component&;

    template<typename Component>
    [[nodiscard]] auto getComponent() -> Component&;

    template<typename Component>
    bool hasComponent() const;

    template<typename Component>
    void removeComponent();

    operator bool() const;
    operator entt::entity() const;
    operator entt::id_type() const;
    operator uint32_t() const;

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;

  private:
    entt::entity m_id = entt::entity(0);
    Scene* m_scene = nullptr;
};

template<typename Component, typename... ARGS>
auto Entity::addComponent(ARGS... args) -> Component&
{
    auto& component = m_Scene->addComponentTo<Component>(*this, std::forward<ARGS>(args)...);
    m_scene->onComponentAdded<Component>(*this, component);
    return component;
}

template<typename Component>
auto Entity::getComponent() -> Component&
{
    return m_scene->getComponentFrom<Component>(*this);
}
template<typename Component>
bool Entity::hasComponent() const
{
    return m_scene->entityHas<Component>(*this);
}
template<typename Component>
void Entity::removeComponent()
{
    m_scene->removeComponent<Component>(*this);
}
}// namespace Meiosis