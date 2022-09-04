#ifndef DISTOPIA_SIMD_SWIZZLE_H
#define DISTOPIA_SIMD_SWIZZLE_H

template <typename VectorT>
inline void Deinterleave2(const VectorT a, const VectorT b, const VectorT c,
                                   VectorT &x, VectorT &y, VectorT &z)
{
}
template <typename VectorT>
inline void Deinterleave4(const VectorT a, const VectorT b, const VectorT c,
                                   VectorT &x, VectorT &y, VectorT &z)
{
    // PRE: a = x0y0z0x1, b = y1z1x2y2, c = z2x3y3z3
    //   __m128 t1 = shuffle_p<_MM_SHUFFLE(2, 1, 3, 2)>(b, c);
    //   __m128 t2 = shuffle_p<_MM_SHUFFLE(1, 0, 2, 1)>(a, b);
    // t1 = x2y2x3y3, t2 = y0z0y1z1
    //   x = shuffle_p<_MM_SHUFFLE(2, 0, 3, 0)>(a, t1);
    //   y = shuffle_p<_MM_SHUFFLE(3, 1, 2, 0)>(t2, t1);
    //   z = shuffle_p<_MM_SHUFFLE(3, 0, 3, 1)>(t2, c);
    // x = x0x1x2x3, y = y0y1y2y3, z = z0z1z2z3
}

template <typename VectorT>
inline void Deinterleave8(const VectorT a, const VectorT b, const VectorT c,
                                   VectorT &x, VectorT &y, VectorT &z)
{
}

template <typename VectorT>
inline void Deinterleave16(const VectorT a, const VectorT b, const VectorT c,
                                    VectorT &x, VectorT &y, VectorT &z)
{
}

#endif // DISTOPIA_SIMD_SWIZZLE_H