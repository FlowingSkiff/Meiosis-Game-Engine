#pragma once
#include "GlobalDefs.hpp"
#include "BaseDynamics.hpp"
#include <array>
namespace Solver
{
template<typename T, typename Constants, typename std::enable_if<std::is_floating_point_v<T>>::type* = nullptr, typename std::enable_if<std::is_base_of<LatticeConstants::Base::ConstantsBase<T>, Constants>::value>::type* = nullptr>
class Cell
{
  private:
    using index_t = Types::index_t;
    using velocity_t = Types::velocity_t<T>;

  public:
    Cell()
    {
        for (auto& v : m_rho)
            v = static_cast<T>(0.);
        for (index_t i = 0; i < m_rho.size(); ++i)
            m_rho.at(i) = Constants::w.at(i);
    }
    ~Cell() {}
    inline T Density() const
    {
        T density = static_cast<T>(0.);
        for (const auto& v : m_rho)
            density += v;
        return density;
    }
    inline velocity_t Velocity() const
    {
        T density = static_cast<T>(0.);
        T vx = static_cast<T>(0.);
        T vy = static_cast<T>(0.);
        for (index_t i = 0; i < m_rho.size(); ++i)
        {
            density += m_rho.at(i);
            vx += Constants::cx.at(i) * m_rho.at(i);
            vy += Constants::cy.at(i) * m_rho.at(i);
        }
        if (density < 1E-14) return { 0., 0. };
        return { vx, vy };
    }

    inline T VelocityMag() const
    {
        const auto vel = Velocity();
        return vel.x * velx + vel.y * vel.y;
    }

    inline auto Equilibrium(T accelXtau, T accelYtau) -> std::array<T, Constants::N>
    {
        std::array<T, Constants::N> result;
        T density = m_rho.at(0);
        T vx = Constants::cx.at(0) * m_rho.at(0);
        T vy = Constants::cy.at(0) * m_rho.at(0);

        for (index_t i = 1; i < Constants::N; ++i)
        {
            density += m_rho.at(i);
            vx = Constants::cx.at(i) * m_rho.at(i);
            vy = Constants::cy.at(i) * m_rho.at(i);
        }

        vx /= density;
        vy /= density;

        vx += accelXtau;
        vy += accelYtau;

        const T vsqr = vx * vx + vy * vy;

        for (index_t i = 0; i < Constants::N; ++i)
        {
            const T term = Constants::cx.at(i) * vx + Constants::cy.at(i) * vy;
            result.at(i) = Constants::w.at(i) * density * (static_cast<T>(1.) + Constants::three * term + Constants::nine_halves * term * term - Constants::three_halves * vsqr);
        }

        return result;
    }
    inline void Collide(T accelXTau, T accelYtau, T tau)
    {
        const auto eq = Equilibrium(accelXTau, accelYtau);
        for (index_t i = 0; i < m_rho.size(); ++i)
            m_rho.at(i) -= (m_rho.at(i) - eq.at(i)) / tau;
    }
    inline void SetRho(T newRho)
    {
        for (auto& rho : m_rho)
            rho = newRho;
    }
    inline void SetRho(index_t dir, T newRho) { m_rho.at(dir) = newRho; }
    inline T Density(index_t dir) const { return m_rho.at(dir); }

  private:
    std::array<T, Constants::N> m_rho;
};
}// namespace Solver
