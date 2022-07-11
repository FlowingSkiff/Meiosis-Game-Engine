#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Core/Timestep.hpp"
#include <entt/entt.hpp>
#include <utility>
#include "Meiosis/Renderer/Shader.hpp"
#include "Meiosis/Renderer/Texture.hpp"
#include "Meiosis/Scene/Components.hpp"
#include "Meiosis/Renderer/RendererBuffer.hpp"
namespace Meiosis
{
class Entity;
class ME_API Scene
{
    using entity_type = entt::entity;

  public:
    Scene();
    ~Scene();
    [[nodiscard]] Entity createEntity(const std::string& name = std::string());
    void deleteEntity(entity_type entity);
    void onUpdate(Timestep ts, Camera& temp_camera);
    void onEditorUpdate(Timestep ts /*, Camera& camera */);
    [[nodiscard]] Entity getCameraEntity();

    void onViewportResize(uint32_t width, uint32_t height);

    template<typename Component>
    void onComponentAdded(entity_type entity_id, Component component);
    template<typename Component, typename... ARGS>
    auto addComponentTo(entity_type entity_id, ARGS... args) -> Component&;
    template<typename Component>
    auto getComponentFrom(entity_type entity_id) -> Component&;
    template<typename Component>
    [[nodiscard]] bool entityHas(entity_type entity_id) const;
    template<typename Component>
    void removeComponentFrom(entity_type entity_id);

    auto loadTexture(const std::string& filename) -> TextureLibrary::TextureID;
    auto loadShader(const std::string& filename) -> ShaderLibrary::ShaderID;
    auto loadMaterial(const std::string& filename, Material::UniformFunction op) -> ShaderLibrary::MaterialID;
    auto getTexture(TextureLibrary::TextureID id) { return m_texture_library.get(id); }
    auto getShader(ShaderLibrary::ShaderID id) { return m_shader_library.getShader(id); }
    auto getMaterial(ShaderLibrary::MaterialID id) { return m_shader_library.getMaterial(id); }

  private:
    entt::registry m_registry;
    uint32_t m_view_width = 0U;
    uint32_t m_view_height = 0U;
    ShaderLibrary m_shader_library;
    TextureLibrary m_texture_library;
};

template<typename Component, typename... ARGS>
auto Scene::addComponentTo(entity_type entity_id, ARGS... args) -> Component&
{
    return m_registry.emplace<Component>(entity_id, std::forward<ARGS>(args)...);
}
template<typename Component>
auto Scene::getComponentFrom(entity_type entity_id) -> Component&
{
    return m_registry.get<Component>(entity_id);
}
template<typename Component>
bool Scene::entityHas(entity_type entity_id) const
{
    return m_registry.any_of<Component>(entity_id);
}
template<typename Component>
void Scene::removeComponentFrom(entity_type entity_id)
{
    m_registry.remove<Component>(entity_id);
}


}// namespace Meiosis