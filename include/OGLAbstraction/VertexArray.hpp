#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
private:
    unsigned int m_RendererID;
};