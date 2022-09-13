#ifndef DISTOPIA_DISTANCES_H
#define DISTOPIA_DISTANCES_H

#include "box.h"
#include "compiler_hints.h"
#include "distopia_type_traits.h"
#include "util.h"
#include "vectorclass.h"
#include "vector_triple.h"

namespace
{
  template <typename VectorT>
  inline VectorT _ortho_pbc(VectorT x0, VectorT x1, VectorT y)
  {
    VectorT d = abs(x0 - x1);
    VectorT y_sub_d = y - d;
    bool sb_all_0 = horizontal_or(sign_bit(y_sub_d));

    if (distopia_likely(sb_all_0))
    {
      return min(d, y_sub_d);
    }
    VectorT x0_pbc = fremainder(x0, y);
    VectorT x1_pbc = fremainder(x1, y);
    d = abs(x0 - x1);
    return min(d, y - d);
  }
}

template <typename VectorT, typename BoxT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const BoxT &box)
{
}

template <typename VectorT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const NoBox<VectorT> &box)
{
  VectorTriple<VectorT> delta = p1 - p2;
  VectorTriple<VectorT> r2 = delta * delta;
  VectorT r = r2.x + r2.y + r2.z;
  return sqrt(r);
}

template <typename VectorT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const OrthogonalBox<VectorT> &box)
{

  VectorT dx = _ortho_pbc(p1.x, p2.x, box.boxlengths.x);
  VectorT dy = _ortho_pbc(p1.y, p2.y, box.boxlengths.y);
  VectorT dz = _ortho_pbc(p1.z, p2.z, box.boxlengths.z);

  VectorT norm_sq = dx * dx;
  norm_sq = mul_add(dy, dy, norm_sq);
  norm_sq = mul_add(dz, dz, norm_sq);

  return sqrt(norm_sq);
}

template <typename VectorT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const TriclinicBox<VectorT> &box)
{
  return VectorT(1.0);
}

#endif // DISTOPIA_DISTANCES_H