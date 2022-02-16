#pragma once
#include <array>
#include <type_traits>
#include "BaseDynamics.hpp"
#include "GlobalDefs.hpp"
namespace Solver::LatticeConstants
{


template<typename T,
    typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
class D2Q9LatticeConstants : public Base::ConstantsBase<T>
{
  private:
    static constexpr T four_ninth = static_cast<T>(4.) / static_cast<T>(9.);
    static constexpr T one_ninth = static_cast<T>(1.) / static_cast<T>(9.);
    static constexpr T one_thirty_sixth = static_cast<T>(1.) / static_cast<T>(36.);
    using index_t = Types::index_t;

  public:
    static constexpr std::array<T, 9> w{ { four_ninth,
        one_ninth,
        one_ninth,
        one_ninth,
        one_ninth,
        one_thirty_sixth,
        one_thirty_sixth,
        one_thirty_sixth } };
    constexpr static std::array<int8_t, 9> cx{ { 0, 1, 0, -1, 0, 1, -1, -1, 1 } };
    constexpr static std::array<int8_t, 9> cy{ { 0, 0, 1, 0, -1, 1, 1, -1, -1 } };
    constexpr static std::array<int8_t, 9> opp{ { 0, 3, 4, 1, 2, 7, 8, 5, 6 } };
    constexpr static index_t N = 9;
    constexpr static index_t D = 2;
    inline constexpr static Types::position_t GetNextPosition(Types::index_t dir, Types::index_t r, Types::index_t c)
    {
        return { { r + cx.at(dir), c + cy.at(dir) } };
    }
};

}// namespace Solver::LatticeConstants
