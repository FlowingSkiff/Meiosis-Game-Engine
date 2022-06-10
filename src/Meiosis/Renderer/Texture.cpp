#include "Meiosis/Renderer/Texture.hpp"
#include "Meiosis/Renderer/Renderer.hpp"

namespace Meiosis
{
auto TextureLibrary::exists(TextureID id) const -> bool
{
    return (m_textures.size() > id);
}
auto TextureLibrary::load(uint32_t width, uint32_t height) -> TextureID
{
    auto texture = Renderer::createTexture2D(width, height);
    m_textures.push_back(texture);
    return m_textures.size() - 1UL;
}
auto TextureLibrary::load(const std::string& file_name) -> TextureID
{
    m_textures.push_back(Renderer::createTexture2D(file_name));
    return m_textures.size() - 1UL;
}
auto TextureLibrary::add(std::shared_ptr<Texture>& texture) -> TextureID
{
    m_textures.push_back(texture);
    return m_textures.size() - 1UL;
}
auto TextureLibrary::get(TextureID id) -> std::shared_ptr<Texture>
{
    return m_textures.at(id);
}
}// namespace Meiosis