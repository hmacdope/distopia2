#ifndef DISTOPIA_SIMD_SWIZZLE_H
#define DISTOPIA_SIMD_SWIZZLE_H

template <typename VectorT>
inline void Deinterleave2(const VectorT a, const VectorT b, const VectorT c,
                          VectorT &x, VectorT &y, VectorT &z)
{
    static_assert(ValuesPerPack<VectorT> == 2,
                  "can only use to load into SIMD datatype of width 2");
    // PRE: a = x0y0, b = z0,x1, c=y1,z1
    x = blend2<0, 3>(a, b);
    // x = x0x1
    y = blend2<1, 2>(a, c);
    // y = y0y1
    z = blend2<0, 3>(b, c);
    // z = z0,z1
}
template <typename VectorT>
inline void Deinterleave4(const VectorT a, const VectorT b, const VectorT c,
                          VectorT &x, VectorT &y, VectorT &z)
{
    static_assert(ValuesPerPack<VectorT> == 4,
                  "can only use to load into SIMD datatype of width 4");

    // PRE: a = x0y0z0x1, b = y1z1x2y2, c = z2x3y3z3
    VectorT t1 = blend4<2, 3, 5, 6>(b, c);
    // t1 = x2y2x3y3,
    VectorT t2 = blend4<1, 2, 4, 5>(a, b);
    // t2 = y0z0y1z1

    x = blend4<0, 3, 4, 6>(a, t1);
    // x = x0x1x2x3
    y = blend4<0, 2, 5, 7>(t2, t1);
    // y = y0y1y2y3
    z = blend4<1, 3, 4, 7>(t2, c);
    // z = z0z1z2z3
}

template <typename VectorT>
inline void Deinterleave8(const VectorT a, const VectorT b, const VectorT c,
                          VectorT &x, VectorT &y, VectorT &z)
{
    static_assert(ValuesPerPack<VectorT> == 8,
                  "can only use to load into SIMD datatype of width 8");
}

template <typename VectorT>
inline void Deinterleave16(const VectorT a, const VectorT b, const VectorT c,
                           VectorT &x, VectorT &y, VectorT &z)
{
    static_assert(ValuesPerPack<VectorT> == 16,
                  "can only use to load into SIMD datatype of width 16");
}

#endif // DISTOPIA_SIMD_SWIZZLE_H