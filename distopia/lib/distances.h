#ifndef DISTOPIA_DISTANCES_H
#define DISTOPIA_DISTANCES_H

#include "box.h"
#include "distopia_type_traits.h"
#include "util.h"
#include "vectorclass.h"
#include "vector_triple.h"



template <bool streaming_store, typename VectorT, typename BoxT>
void CalcBondsInner(const VectorToScalarT<VectorT> *coords0,
                    const VectorToScalarT<VectorT> *coords1,
                    const VectorToScalarT<VectorT> *box, std::size_t n,
                    VectorToScalarT<VectorT> *out) {
  auto vecbox = BoxT(box);
  VectorTriple<VectorT> c0{}, c1{};
  std::size_t i = 0;
  if (n % ValuesPerPack<VectorT>) {
    c0.load(coords0);
    c1.load(coords1);
    VectorT result = Distance3DWithBoundary(c0, c1, vecbox);
    // TODO constexpr if with CXX17 support
    if (streaming_store) {
      genericstream(out, result);
    } else {
      genericstore(out, result);
    }
    i += n % ValuesPerPack<VectorT>;
  }
  for (; i < n; i += ValuesPerPack<VectorT>) {
    c0.load(&coords0[3 * i]);
    c1.load(&coords1[3 * i]);

    VectorT result = Distance3DWithBoundary(c0, c1, vecbox);
    // TODO constexpr if with CXX17 support
    if (streaming_store) {
      genericstream(&out[i], result);
    } else {
      genericstore(&out[i], result);
    }
  }
  // TODO constexpr if with CXX17 support
  if (streaming_store) {
    _mm_mfence();
  }
}


#endif // DISTOPIA_DISTANCES_H