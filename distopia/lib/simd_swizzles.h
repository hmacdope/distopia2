#ifndef DISTOPIA_SIMD_SWIZZLE_H
#define DISTOPIA_SIMD_SWIZZLE_H

#include "distopia_type_traits.h"
#include "vectorclass.h"

template <typename VectorT>
inline void Deinterleave2(const VectorT a, const VectorT b, const VectorT c,
                          VectorT &x, VectorT &y, VectorT &z)
{

    // TODO: Can these be done better with gather or lookup functions?
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
    // TODO: Can these be done better with gather or lookup functions?
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
    // TODO: Can these be done better with gather or lookup functions?
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
    // TODO: Can these be done better with gather or lookup functions?
    static_assert(ValuesPerPack<VectorT> == 16,
                  "can only use to load into SIMD datatype of width 16");

    // PRE: a = x0y0z0x1y1z1x2y2z2x3y3z3x4y4z4x5
    // PRE: b = y5z5x6y6z6x7y7z7x8y8z8x9y9z9x10y10
    // PRE: c = z10x11y11z11x12y12z12x13y13z13x14y14z14x15y15z15

    // split into registers and apply same blends as Deinterleave8,
    // this is a little lazy as we could possibly get better lane crossing
    // instructions out of AVX512
    // hopefully the use of 2 independent pipelines is faster

    HalfVectorT<VectorT> a_low = a.get_low();   // a equivalent
    HalfVectorT<VectorT> a_high = a.get_high(); // b equivalent
    HalfVectorT<VectorT> b_low = b.get_low();   // c equivalent
    HalfVectorT<VectorT> x_low;
    HalfVectorT<VectorT> y_low;
    HalfVectorT<VectorT> z_low;

    Deinterleave8(a_low, a_high, b_low, x_low, y_low, z_low);

    HalfVectorT<VectorT> b_high = b.get_high(); // a equivalent
    HalfVectorT<VectorT> c_low = c.get_low();   // b equivalent
    HalfVectorT<VectorT> c_high = c.get_high(); // c equivalent
    HalfVectorT<VectorT> x_high;
    HalfVectorT<VectorT> y_high;
    HalfVectorT<VectorT> z_high;

    Deinterleave8(b_high, c_low, c_high, x_high, y_high, z_high);

    x = concatenate2(x_low, x_high);
    y = concatenate2(y_low, y_high);
    z = concatenate2(z_low, z_high);
}

// As the deinterleaves were generic now we need overloads for each option
inline void Deinterleave(Vec2d a, Vec2d b, Vec2d c, Vec2d &x, Vec2d &y, Vec2d &z)
{
    Deinterleave2(a, b, c, x, y, z);
}

inline void Deinterleave(Vec4f a, Vec4f b, Vec4f c, Vec4f &x, Vec4f &y, Vec4f &z)
{
    Deinterleave4(a, b, c, x, y, z);
}

inline void Deinterleave(Vec4d a, Vec4d b, Vec4d c, Vec4d &x, Vec4d &y, Vec4d &z)
{
    Deinterleave4(a, b, c, x, y, z);
}

inline void Deinterleave(Vec8f a, Vec8f b, Vec8f c, Vec8f &x, Vec8f &y, Vec8f &z)
{
    Deinterleave8(a, b, c, x, y, z);
}

inline void Deinterleave(Vec8d a, Vec8d b, Vec8d c, Vec8d &x, Vec8d &y, Vec8d &z)
{
    Deinterleave8(a, b, c, x, y, z);
}

inline void Deinterleave(Vec16f a, Vec16f b, Vec16f c, Vec16f &x, Vec16f &y, Vec16f &z)
{
    Deinterleave16(a, b, c, x, y, z);
}

#endif // DISTOPIA_SIMD_SWIZZLE_H