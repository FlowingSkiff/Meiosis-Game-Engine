#pragma once
#include <type_traits>
#include <array>
namespace Solver::Types
{
namespace BaseType
{
    template<typename T, typename std::enable_if<std::is_floating_point_v<T>>::type* = nullptr>
    struct velocity_base_t
    {
        T x, y;
    };
}// namespace BaseType
using index_t = uint16_t;
template<typename T, typename std::enable_if<std::is_floating_point_v<T>>::type* = nullptr>
using velocity_t = BaseType::velocity_base_t<T>;
using position_t = std::array<index_t, 2>;
}// namespace Solver::Types