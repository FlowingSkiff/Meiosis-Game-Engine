#include "Meiosis/Renderer/RendererBuffer.hpp"

namespace Meiosis
{
BufferLayout::BufferLayout(std::initializer_list<BufferObject> elements) : m_elements(elements)
{
    calculateOffsetAndStride();
}
void BufferLayout::calculateOffsetAndStride()
{
    size_t offset = 0u;
    m_stride = 0u;
    for (auto& element : m_elements)
    {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
    }
}
}// namespace Meiosis