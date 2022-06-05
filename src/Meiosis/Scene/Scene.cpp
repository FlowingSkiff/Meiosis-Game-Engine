#include <Meiosis/Scene/Scene.hpp>
#include <Meiosis/Scene/Components.hpp>
#include <Meiosis/Scene/Entity.hpp>

namespace Meiosis
{
Scene::Scene()
{
}
Scene::~Scene()
{
}
Entity Scene::createEntity(const std::string& name)
{
    Entity entity{ m_registry.create(), this };
    entity.addComponent<TransformComponent>();
    auto& tag = entity.addComponent<TagComponent>();
    tag.tag = (name.empty()) ? "Unnamed" : name;
    return entity;
}
void Scene::deleteEntity(Entity entity)
{
    m_registry.destroy(entity);
}
void Scene::onUpdate([[maybe_unused]] Timestep ts)
{
    {
        // Scripts
    }

    Camera* main_camera = nullptr;
    glm::mat4 camera_transform;
    auto view = m_registry.view<TransformComponent, CameraComponent>();
    for (auto entity : view)
    {
        auto [c_transform, c_camera] = view.get<TransformComponent, CameraComponent>(entity);
        if (c_camera.is_primary)
        {
            main_camera = &(c_camera.camera);
            camera_transform = c_transform.getTransform();
            break;
        }
    }
    if (main_camera != nullptr)
    {
    }
}
void Scene::onEditorUpdate([[maybe_unused]] Timestep ts /*, Camera& camera */)
{
}
Entity Scene::getCameraEntity()
{
    auto view = m_registry.view<CameraComponent>();
    for (auto entity : view)
    {
        const auto& camera = view.get<CameraComponent>(entity);
        if (camera.is_primary)
            return { entity, this };
    }
    return {};
}

void Scene::onViewportResize(uint32_t width, uint32_t height)
{
    m_view_width = width;
    m_view_height = height;

    auto view = m_registry.view<CameraComponent>();
    for (auto entity : view)
    {
        auto& camera = view.get<CameraComponent>(entity);
        if (!camera.has_fixed_aspect_ratio)
            camera.camera.setViewportSize(m_view_width, m_view_height);
    }
}


template<>
void Scene::onComponentAdded<TransformComponent>([[maybe_unused]] uint32_t entity_id, [[maybe_unused]] TransformComponent component)
{
}

template<>
void Scene::onComponentAdded<TagComponent>([[maybe_unused]] uint32_t entity_id, [[maybe_unused]] TagComponent component)
{
}
template<>
void Scene::onComponentAdded<MeshComponent>([[maybe_unused]] uint32_t entity_id, [[maybe_unused]] MeshComponent component)
{
}
template<>
void Scene::onComponentAdded<CameraComponent>([[maybe_unused]] uint32_t entity_id, [[maybe_unused]] CameraComponent component)
{
    if (m_view_width > 0U && m_view_height > 0U)
        component.camera.setViewportSize(m_view_width, m_view_height);
}


template<typename Component>
void Scene::onComponentAdded(uint32_t entity_id, Component component)
{
    assert(false);
}
}// namespace Meiosis