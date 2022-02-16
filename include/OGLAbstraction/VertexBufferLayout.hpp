#pragma once
#include <vector>
#include "glad\glad.h"
#include <cassert>
#include <iostream>
class VertexBufferLayout
{
public:
    VertexBufferLayout(): m_Stride(0)
    {

    }
    ~VertexBufferLayout() { }
public:
    struct VertexBufferElement
    {
        unsigned int count;
        unsigned int type;
        bool normalized;
        static unsigned int GetSizeOfType(const unsigned int& type)
        {
            switch (type)
            {
                case GL_FLOAT: return 4;
                case GL_UNSIGNED_INT: return 4;
                case GL_UNSIGNED_BYTE: return 1;
            }
            assert(false);
            return 0;
        }
    };
public:
    template<typename T>
    void Push(unsigned int count)
    {
        assert(false);
    }
    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
private:
    unsigned int m_Stride;
    std::vector<VertexBufferElement> m_Elements;
};



template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({count, GL_FLOAT, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}
template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({count, GL_UNSIGNED_INT, false});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}
template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({count, GL_UNSIGNED_BYTE, true});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}