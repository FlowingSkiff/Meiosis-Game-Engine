#pragma once
#include "Meiosis/Core/Core.hpp"
#include <string>
#include <memory>
#include <vector>

namespace Meiosis
{
class ME_API Texture
{
  public:
    explicit Texture() = default;
    virtual ~Texture() = default;
    Texture(const Texture&) = default;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) = default;
    Texture& operator=(Texture&&) = default;
    [[nodiscard]] virtual auto getWidth() const -> uint32_t = 0;
    [[nodiscard]] virtual auto getHeight() const -> uint32_t = 0;
    [[nodiscard]] virtual auto getRendererID() const -> uint32_t = 0;

    virtual void setData(void* data, uint32_t size) = 0;
    virtual void bind(uint32_t slot = 0) const = 0;
    [[nodiscard]] virtual bool isLoaded() const = 0;
    virtual bool operator==(const Texture& other) const = 0;
};

class ME_API TextureLibrary
{
  public:
    using TextureID = size_t;
    TextureLibrary() = default;
    [[nodiscard]] bool exists(TextureID id) const;
    [[nodiscard]] auto add(uint32_t width, uint32_t height) -> TextureID;
    [[nodiscard]] auto add(const std::string& file_name) -> TextureID;
    [[nodiscard]] auto add(std::shared_ptr<Texture>& texture) -> TextureID;
    [[nodiscard]] auto get(TextureID id) -> std::shared_ptr<Texture>;

  private:
    std::vector<std::shared_ptr<Texture>> m_textures;
};
}// namespace Meiosis