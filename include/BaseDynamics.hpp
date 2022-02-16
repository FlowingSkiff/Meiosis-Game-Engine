#pragma once
#include <type_traits>
#include "GlobalDefs.hpp"
namespace Solver::LatticeConstants::Base
{
template<typename T, typename std::enable_if<std::is_floating_point_v<T>>::type* = nullptr>
struct ConstantsBase
{
    constexpr static T three = static_cast<T>(3.);
    constexpr static T nine_halves = static_cast<T>(9.) / static_cast<T>(2.);
    constexpr static T three_halves = static_cast<T>(3.0) / static_cast<T>(2.0);
    inline constexpr static virtual Types::position_t GetNextPosition(Types::index_t dir, Types::index_t r, Types::index_t c) = 0;
};
}// namespace Solver::LatticeConstants::Base