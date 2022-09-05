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

    // PRE: a = x0y0z0x1y1z1x2y2, b = z2x3y3z3x4y4z4x5, c = y5z5x6y6z6x7y7z7

    // blend halves
    VectorT m1 = blend8<0, 1, 2, 3, 12, 13, 14, 15>(a, b);
    // m1 = x0y0z0x1x4y4z4x5
    VectorT m2 = blend8<4, 5, 6, 7, 8, 9, 10, 11>(a, c);
    // m2 = y1z1x2y2y5z5x6y6
    VectorT m3 = blend8<0, 1, 2, 3, 12, 13, 14, 15>(b, c);
    // m3 = z2x3y3z3z6x7y7z7

    VectorT t1 = blend8<2, 3, 9, 10, 6, 7, 13, 14>(m2, m3);
    // t1 = x2y2x3y3x6y6x7y7
    VectorT t2 = blend8<1, 2, 8, 9, 5, 6, 12, 13>(m1, m2);
    // t2 = y0z0y1z1y4z4y5z5

    x = blend8<0, 3, 8, 10, 4, 7, 12, 14>(m1, t1);
    // x = x0x1x2x3x4x5x6x7
    y = blend8<0, 2, 9, 11, 4, 6, 13, 15>(t2, t1);
    // y = y0y1y2y3y4y5y6y7
    z = blend8<1, 3, 8, 11, 5, 7, 12, 15>(t2, m3);
    // z = z0z1z2z3z4z5z6z7
}

template <typename VectorT>
inline void Deinterleave16(const VectorT a, const VectorT b, const VectorT c,
                           VectorT &x, VectorT &y, VectorT &z)
{
    static_assert(ValuesPerPack<VectorT> == 16,
                  "can only use to load into SIMD datatype of width 16");
}

#endif // DISTOPIA_SIMD_SWIZZLE_H