#ifndef DISTOPIA_CALC_BONDS_H
#define DISTOPIA_CALC_BONDS_H

#include "box.h"
#include "distances.h"
#include "distopia_type_traits.h"
#include "util.h"
#include "vectorclass.h"
#include "vector_triple.h"

template <typename VectorT, typename BoxT>
void CalcBondsInner(const VectorToScalarT<VectorT> *coords0,
                    const VectorToScalarT<VectorT> *coords1,
                    const VectorToScalarT<VectorT> *box, std::size_t n,
                    VectorToScalarT<VectorT> *out)
{
  auto vecbox = BoxT(box);
  VectorTriple<VectorT> c0{}, c1{};
  std::size_t i = 0;
  if (n % ValuesPerPack<VectorT>)
  {
    c0.load_and_deinterleave(coords0);
    c1.load_and_deinterleave(coords1);
    VectorT result = _PBC_Distance(c0, c1, vecbox);
    result.store(out);
    i += n % ValuesPerPack<VectorT>;
  }
  for (; i < n; i += ValuesPerPack<VectorT>)
  {
    c0.load_and_deinterleave(&coords0[3 * i]);
    c1.load_and_deinterleave(&coords1[3 * i]);

    VectorT result = _PBC_Distance(c0, c1, vecbox);
    result.store(&out[i], result);
  }
}

#endif // DISTOPIA_CALC_BONDS_H