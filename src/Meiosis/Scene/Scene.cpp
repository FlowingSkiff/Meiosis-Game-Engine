#include <Meiosis/Scene/Scene.hpp>
#include <Meiosis/Scene/Components.hpp>
#include <Meiosis/Scene/Entity.hpp>
#include <Meiosis/Renderer/Renderer.hpp>

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
void Scene::deleteEntity(entity_type entity)
{
    m_registry.destroy(entity);
}
void Scene::onUpdate([[maybe_unused]] Timestep ts, Camera& temp_camera)
{
    {
        /*
        for (auto script : m_registry<ScripComponent>())
        {
            script(ts);
        }
        */
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
    auto mesh_view = m_registry.view<TagComponent, MeshComponent>();
    Renderer::beginScene(temp_camera);
    for (auto entity : mesh_view)
    {
        auto [tag, mesh] = mesh_view.get<TagComponent, MeshComponent>(entity);
        uint32_t bind_index = 0U;
        for (auto texture : mesh.textures)
        {
            m_texture_library.get(texture)->bind(bind_index++);
        }
        if (mesh.is_material)
        {
            Renderer::submit(m_shader_library.getMaterial(mesh.material), mesh.vertices);
        }
        else
        {
            Renderer::submit(m_shader_library.getShader(mesh.shader), mesh.vertices);
        }
    }
    Renderer::endScene();
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
void Scene::onComponentAdded<TransformComponent>([[maybe_unused]] entity_type entity_id, [[maybe_unused]] TransformComponent component)
{
}

template<>
void Scene::onComponentAdded<TagComponent>([[maybe_unused]] entity_type entity_id, [[maybe_unused]] TagComponent component)
{
}
template<>
void Scene::onComponentAdded<MeshComponent>([[maybe_unused]] entity_type entity_id, [[maybe_unused]] MeshComponent component)
{
}
template<>
void Scene::onComponentAdded<CameraComponent>([[maybe_unused]] entity_type entity_id, [[maybe_unused]] CameraComponent component)
{
    if (m_view_width > 0U && m_view_height > 0U)
        component.camera.setViewportSize(m_view_width, m_view_height);
}


template<typename Component>
void Scene::onComponentAdded(entity_type entity_id, Component component)
{
    assert(false);
}

auto Scene::loadTexture(const std::string& filename) -> TextureLibrary::TextureID
{
    return m_texture_library.load(filename);
}
auto Scene::loadShader(const std::string& filename) -> ShaderLibrary::ShaderID
{
    return m_shader_library.loadShader(filename);
}

auto Scene::loadMaterial(const std::string& filename, Material::UniformFunction op) -> ShaderLibrary::MaterialID
{
    return m_shader_library.loadMaterial(filename, op);
}

}// namespace Meiosis