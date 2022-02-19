#pragma once
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
class Renderer
{
  public:
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& s);
    static void Clear(const glm::vec4 color = { 0.2f, 0.3f, 0.3f, 1.0f });

  private:
};