#pragma once
#include <string>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

public:
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
private:
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer = nullptr;
    int m_Width, m_Height, m_BPP;
};