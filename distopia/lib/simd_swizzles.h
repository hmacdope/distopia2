#ifndef DISTOPIA_SIMD_SWIZZLE_H
#define DISTOPIA_SIMD_SWIZZLE_H

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

    // split into registers and apply same blends as Deinterleave8, this is a little lazy but
    // hopefully the use of 2 independent pipelines is faster

    HalfVectorT<VectorT> a_low = a.get_low(); // a
    HalfVectorT<VectorT> a_high = a.get_high(); // b
    HalfVectorT<VectorT> b_low = b.get_low(); // c


    // blend halves
    HalfVectorT<VectorT> m1_low = blend8<0, 1, 2, 3, 12, 13, 14, 15>(a_low, a_high);
    // m1 = x0y0z0x1x4y4z4x5
    HalfVectorT<VectorT> m2_low = blend8<4, 5, 6, 7, 8, 9, 10, 11>(a_low, b_low);
    // m2 = y1z1x2y2y5z5x6y6
    HalfVectorT<VectorT> m3_low = blend8<0, 1, 2, 3, 12, 13, 14, 15>(a_high, b_low);
    // m3 = z2x3y3z3z6x7y7z7

    HalfVectorT<VectorT> t1_low = blend8<2, 3, 9, 10, 6, 7, 13, 14>(m2_low, m3_low);
    // t1 = x2y2x3y3x6y6x7y7
    HalfVectorT<VectorT> t2_low = blend8<1, 2, 8, 9, 5, 6, 12, 13>(m1_low, m2_low);
    // t2 = y0z0y1z1y4z4y5z5

    HalfVectorT<VectorT> x_low = blend8<0, 3, 8, 10, 4, 7, 12, 14>(m1_low, t1_low);
    // x = x0x1x2x3x4x5x6x7
    HalfVectorT<VectorT> y_low = blend8<0, 2, 9, 11, 4, 6, 13, 15>(t2_low, t1_low);
    // y = y0y1y2y3y4y5y6y7
    HalfVectorT<VectorT> z_low = blend8<1, 3, 8, 11, 5, 7, 12, 15>(t2_low, m3_low);
    // z = z0z1z2z3z4z5z6z7


    HalfVectorT<VectorT> b_high = b.get_high(); // a
    HalfVectorT<VectorT> c_low = c.get_low(); // b
    HalfVectorT<VectorT> c_high = c.get_high(); // c

    // blend halves
    HalfVectorT<VectorT> m1_high = blend8<0, 1, 2, 3, 12, 13, 14, 15>(b_high, c_low);
    // m1 = x0y0z0x1x4y4z4x5
    HalfVectorT<VectorT> m2_high = blend8<4, 5, 6, 7, 8, 9, 10, 11>(b_high, c_high);
    // m2 = y1z1x2y2y5z5x6y6
    HalfVectorT<VectorT> m3_high = blend8<0, 1, 2, 3, 12, 13, 14, 15>(c_low, c_high);
    // m3 = z2x3y3z3z6x7y7z7

    HalfVectorT<VectorT> t1_high = blend8<2, 3, 9, 10, 6, 7, 13, 14>(m2_high, m3_high);
    // t1 = x2y2x3y3x6y6x7y7
    HalfVectorT<VectorT> t2_high = blend8<1, 2, 8, 9, 5, 6, 12, 13>(m1_high, m2_high);
    // t2 = y0z0y1z1y4z4y5z5

    HalfVectorT<VectorT> x_high = blend8<0, 3, 8, 10, 4, 7, 12, 14>(m1_high, t1_high);
    // x = x0x1x2x3x4x5x6x7
    HalfVectorT<VectorT> y_high = blend8<0, 2, 9, 11, 4, 6, 13, 15>(t2_high, t1_high);
    // y = y0y1y2y3y4y5y6y7
    HalfVectorT<VectorT> z_high = blend8<1, 3, 8, 11, 5, 7, 12, 15>(t2_high, m3_high);
    // z = z0z1z2z3z4z5z6z7

    x = concatenate2(x_low,x_high);
    y = concatenate2(y_low, y_high);
    z = concatenate2(z_low, z_high);

}

#endif // DISTOPIA_SIMD_SWIZZLE_H