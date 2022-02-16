#pragma once
#include <type_traits>
#include "GlobalDefs.hpp"
#include "Cell.hpp"
#include <Eigen/Eigen>
#include <variant>
#include "Units.hpp"
namespace Solver
{
template<typename T, typename Constants, typename std::enable_if<std::is_floating_point_v<T>>::type* = nullptr, typename std::enable_if<std::is_base_of<LatticeConstants::Base::ConstantsBase<T>, Constants>::value>::type* = nullptr>
class Lattice
{
  private:
    static constexpr Eigen::StorageOptions DataOrder = Eigen::ColMajor;
    using lattice_t = Eigen::Matrix<Cell<T, Constants>, Eigen::Dynamic, Eigen::Dynamic, DataOrder>;
    using obstacle_t = Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic, DataOrder>;
    using result_t = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, DataOrder>;
    using index_t = Types::index_t;

  public:
    Lattice(const Units2D _units, index_t nrows, index_t ncols, const obstacle_t& obstacle) : m_lattice(), m_obstacle(), m_results_type(ResultsType::Velocity), external_force_x(0), external_force_y(0), m_units(_units)
    {
        m_lattice = lattice_t(nrows, ncols);
        m_obstacle = obstacle;
        m_results = results_t(nrows, ncols).setZero();
        Init();
    }

    ~Lattice() {}
    void Init()
    {
        for (index_t j = 0; j < m_lattice.cols(); ++j)
        {
            for (index_t i = 0; i < m_lattice.rows(); ++i)
            {
                if (m_obstacle(i, j) || (i == 0) || (i == m_lattice.rows() - 1))
                {
                    lattice(i, j).SetRho(0.);
                }
            }
        }
    }

    void CollideAndStream(lattice_t& latticeWork)
    {
        const index_t LatticeRows = m_lattice.rows();
        const index_t LatticeRowsM1 = LatticeRows - 1;
        const index_t LatticeRowsM2 = LatticeRows - 2;
        const index_t LatticeCols = m_lattice.cols();
        const index_t LatticeColsM1 = LatticeCols - 1;
        const index_t LatticeColsM2 = LatticeCols - 2;

        const T accelXtau = external_force_x * m_units.GetTau();
        const T accelYtau = external_force_y * m_units.GetTau();

        const index_t start_col = 0u;
        const index_t end_col = m_lattice.cols();

        if (start_col < 2)
        {
        }

        for (index_t c = (start_col < 2) ? 2 : start_col;
             c < ((end_col >= LatticeColsM2) ? LatticeColsM2 : end_col);
             c++)
        {
            CollideAndStreamSlow(c, 0);
            CollideAndStreamSlow(c, 1);
            for (index_t r = 2; r < LatticeRowsM2; ++r)
                CollideAndStreamFast(c, r, latticeWork);
            CollideAndStreamSlow(c, LatticeColsM2);
            CollideAndStreamSlow(c, LatticeColsM1);
        }

        if (end_col >= LatticeColsM2)
        {
        }
    }

    void Simulate()
    {
        auto latticeWork = lattice_t(m_lattice.rows(), m_lattice.cols());
        index_t timesteps = 1000;
        for (index_t t = 0; t < timesteps; ++t)
        {
            CollideAndStream();
        }
    }

  private:
    void CollideAndStreamFast(index_t c, index_t r, lattice_t& latticeWork)
    {
        if (!m_obstacle(r, c))
            m_lattice(r, c).Collide(external_force_x, external_force_y, m_units.GetTau());

        for (index_t dir = 0u; dir < Constants::N; ++dir)
        {
            auto direction = dir;
            auto pos = Constants::GetNextPosition(dir, r, c);
            if (m_obstacle(pos.at(1), pos.at(0))) direction = Constants::opp.at(dir);
            latticeWork(pos.at(1), pos.at(0)).SetRho(direction) = m_lattice(r, c).Density(dir);
        }
    }
    void CollideAndStreamSlow(index_t c, index_t r, lattice_t& latticeWork)
    {
    }

  public:
    enum class ResultsType {
        Density = 0,
        Velocity,
        Vorticity
    };

  private:
    lattice_t m_lattice;
    obstacle_t m_obstacle;
    ResultsType m_results_type;// Can store one of the result types
    result_t m_results;
    T external_force_x, external_force_y;// TODO: external force tensor
    const Units2D m_units;

  protected:
};
}// namespace Solver
