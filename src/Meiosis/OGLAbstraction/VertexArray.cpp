#include "OGLAbstraction/VertexArray.hpp"
#include "glad\glad.h"
VertexArray::VertexArray(): m_RendererID(0)
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}
void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0u;
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements.at(i);
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, 
            (element.normalized ? GL_TRUE : GL_FALSE), layout.GetStride(), (void*)offset );
        offset += element.count * VertexBufferLayout::VertexBufferElement::GetSizeOfType(element.type);
    }
}