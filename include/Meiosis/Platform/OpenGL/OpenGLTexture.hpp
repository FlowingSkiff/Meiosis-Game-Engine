#pragma once
#include "Meiosis/Core/Core.hpp"
#include "Meiosis/Renderer/Texture.hpp"
#include <string>
#include <glad/glad.h>
namespace Meiosis
{
class ME_API OpenGLTexture2D : public Texture
{
  public:
    OpenGLTexture2D(uint32_t width, uint32_t height);
    OpenGLTexture2D(const std::string& path);
    virtual ~OpenGLTexture2D();

    virtual auto getWidth() const -> uint32_t override;
    virtual auto getHeight() const -> uint32_t override;
    virtual auto getRendererID() const -> uint32_t override;

    virtual void setData(void* data, uint32_t size) override;
    virtual void bind(uint32_t slot = 0) const override;
    virtual bool isLoaded() const override;
    virtual bool operator==(const Texture& other) const override;

  private:
    std::string m_path;
    bool m_is_loaded;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_renderer_id;
    GLenum m_internal_format;
    GLenum m_data_format;
};
}// namespace Meiosis