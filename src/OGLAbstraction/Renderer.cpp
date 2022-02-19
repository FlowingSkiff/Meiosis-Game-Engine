#include "Renderer.hpp"

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader)
{
    shader.Bind();
    vao.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(glm::vec4 color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}