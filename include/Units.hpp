#pragma once
#include <type_traits>
#include "GlobalDefs.hpp"
namespace Solver
{
template<typename T, typename std::enable_if<std::is_floating_point_v<T>>::type* = nullptr>
class Units2D
{
  private:
    using index_t = Types::index_t;

  public:
    Units2D(T physicalU_, T latticeU_, T Re_, T physicalLength_, index_t resolution_, T lx_, T ly_) : physicalU(physicalU_),
                                                                                                      latticeU(latticeU_),
                                                                                                      Re(Re_),
                                                                                                      physicalLength(physicalLength_),
                                                                                                      resolution(resolution_),
                                                                                                      lx(lx_),
                                                                                                      ly(ly_)
    {
    }

    Units2D(T latticeU_, T Re_, index_t resolution_, T lx_, T ly_) : physicalU(1),
                                                                     latticeU(latticeU_),
                                                                     Re(Re_),
                                                                     physicalLength(1),
                                                                     resolution(resolution_),
                                                                     lx(lx_),
                                                                     ly(ly_)
    {
    }

  public:
    T GetLatticeU() const { return latticeU; }
    T GetPhysicalU() const { return physicalU; }
    T GetRe() const { return Re; }
    T GetPhysicalLength() const { return physicalLength; }
    index_t GetResolution() const { return resolution; }
    T GetLx() const { return lx; }
    T GetLy() const { return ly; }

  public:
    T GetDeltaX() const { return static_cast<T>(GetPhysicalLength()) / static_cast<T>(GetResolution();) }
    T GetDeltaT() const { return GetDeltaX() * GetLatticeU() / GetPhysicalU(); }
    index_t NCell(T l) const { return static_cast<index_t>(l / GetDeltaX() + static_cast<T>(0.5)); }
    index_t NStep(T t) const { return static_cast<index_t>(t / GetDeltaT() + static_cast<T>(0.5)); }
    index_t GetNx(bool offLattice = false) const { return NCell(GetLx()) + 1 + static_cast<int>(offLattice); }
    index_t GetNx(bool offLattice = false) const { return NCell(GetLy()) + 1 + static_cast<int>(offLattice); }
    T GetLatticeNu() const { return GetLatticeU() * static_cast<T>(GetResolution()) / Re; }
    T GetTau() const { return static_cast<T>(3.) * GetLatticeNu() + static_cast<T>(0.5); }
    T GetOmega() const { return static_cast<T>(1.) / GetTau(); }

  private:
  protected:
    T physicalU, latticeU, Re, physicalLength;
    index_t resolution;
    T lx, ly;
};
}// namespace Solver
