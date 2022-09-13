#ifndef DISTOPIA_DISTANCES_H
#define DISTOPIA_DISTANCES_H

#include "box.h"
#include "distopia_type_traits.h"
#include "util.h"
#include "vectorclass.h"
#include "vector_triple.h"

template <typename VectorT, typename BoxT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const BoxT &box)
{
}

template <typename VectorT, typename BoxT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const NoBox<VectorT> &box)
{
  VectorTriple<VectorT> delta = p1 - p2;
  VectorTriple<VectorT> r2 = delta * delta;
  VectorT r = r2.x + r2.y + r2.z;
  return sqrt(r);
}

template <typename VectorT, typename BoxT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const OrthogonalBox<VectorT> &box)
{
}

template <typename VectorT, typename BoxT>
inline VectorT PBC_Distance(const VectorTriple<VectorT> &p1, const VectorTriple<VectorT> &p2, const TriclinicBox<VectorT> &box)
{
}

#endif // DISTOPIA_DISTANCES_H