#include <Meiosis/Scene/Entity.hpp>

namespace Meiosis
{
Entity::Entity(entt::entity id) : m_id(id) {}
Entity::Entity(entt::entity id, Scene* scene) : m_id(id), m_scene(scene) {}

void Entity::setScene(Scene* scene)
{
    m_scene = scene;
}

Entity::operator bool() const
{
    return m_id != entt::entity(0);
}
Entity::operator entt::entity() const
{
    return m_id;
}
Entity::operator entt::id_type() const
{
    return static_cast<entt::id_type>(m_id);
}

bool Entity::operator==(const Entity& other) const
{
    return m_id == other.m_id && m_scene == other.m_scene;
}
bool Entity::operator!=(const Entity& other) const
{
    return m_id != other.m_id && m_scene != other.m_scene;
}
}// namespace Meiosis