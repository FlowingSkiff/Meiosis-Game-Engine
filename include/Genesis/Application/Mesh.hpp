#pragma once
#include <type_traits>
namespace impl
{
template<typename Type, std::enable_if_t<std::is_floating_point_v<Type>, bool> = true>
struct VertexImpl
{
    Type position[3];
    Type normals[3];
    Type texture[2];
};
}// namespace impl

using Vertex = impl::VertexImpl<float>;
using DoubleVertex = impl::VertexImpl<double>;

class Mesh
{
};