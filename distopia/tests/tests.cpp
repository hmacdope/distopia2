#include <numeric>
#include <iostream>

#include "gtest/gtest.h"

#include "../lib/example.h"
#include "../lib/simd_swizzles.h"
#include "../lib/vector_triple.h"

using testing::Types;
typedef Types<Vec4f, Vec8f, Vec16f, Vec2d, Vec4d, Vec8d> Implementations;
typedef Types<Vec4f, Vec4d> Width4Implementations;
typedef Types<Vec8f, Vec8d> Width8Implementations;

template <typename T>
class VectorTripleTest : public ::testing::Test
{
public:
    // blank, we do all the stuff in each test
};

TYPED_TEST_SUITE(VectorTripleTest, Implementations);

TYPED_TEST(VectorTripleTest, Construct)
{
    TypeParam x(1);

    auto vt = VectorTriple<TypeParam>(x, x, x);

    VectorToScalarT<TypeParam> out_buffer0[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer1[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer2[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer3[ValuesPerPack<TypeParam>];

    x.store(out_buffer0);
    vt.x.store(out_buffer1);
    vt.y.store(out_buffer2);
    vt.z.store(out_buffer3);

    for (int i = 0; i < vt.size; i++)
    {
        ASSERT_FLOAT_EQ(out_buffer0[i], out_buffer1[i]);
        ASSERT_FLOAT_EQ(out_buffer0[i], out_buffer2[i]);
        ASSERT_FLOAT_EQ(out_buffer0[i], out_buffer3[i]);
    }
}

TYPED_TEST(VectorTripleTest, LoadFromBuffer)
{
    auto vt = VectorTriple<TypeParam>();

    VectorToScalarT<TypeParam> input_buffer[3 * ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer1[3 * ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer2[3 * ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer3[3 * ValuesPerPack<TypeParam>];

    std::iota(std::begin(input_buffer), std::end(input_buffer), 0);

    vt.load(input_buffer);
    vt.x.store(out_buffer1);
    vt.y.store(out_buffer2);
    vt.z.store(out_buffer3);

    for (int j = 0; j < vt.size; j++)
    {
        ASSERT_FLOAT_EQ(input_buffer[j], out_buffer1[j]);
        ASSERT_FLOAT_EQ(input_buffer[ValuesPerPack<TypeParam> + j], out_buffer2[j]);
        ASSERT_FLOAT_EQ(input_buffer[ValuesPerPack<TypeParam> * 2 + j], out_buffer3[j]);
    }
}

// only Vec2d has width = 2 so no need for typed test
TEST(Deinterleave2Test, Deinterleave)
{
    Vec2d a(0, 1);
    Vec2d b(2, 3);
    Vec2d c(4, 5);
    Vec2d x;
    Vec2d y;
    Vec2d z;

    double out_buffer1[2];
    double out_buffer2[2];
    double out_buffer3[2];

    Deinterleave2(a, b, c, x, y, z);

    x.store(out_buffer1);
    y.store(out_buffer2);
    z.store(out_buffer3);

    ASSERT_DOUBLE_EQ(out_buffer1[0], 0);
    ASSERT_DOUBLE_EQ(out_buffer1[1], 3);
    ASSERT_DOUBLE_EQ(out_buffer2[0], 1);
    ASSERT_DOUBLE_EQ(out_buffer2[1], 4);
    ASSERT_DOUBLE_EQ(out_buffer3[0], 2);
    ASSERT_DOUBLE_EQ(out_buffer3[1], 5);
}

template <typename T>
class Deinterleave4Test : public ::testing::Test
{
public:
    // blank, we do all the stuff in each test
};

TYPED_TEST_SUITE(Deinterleave4Test, Width4Implementations);

TYPED_TEST(Deinterleave4Test, Deinterleave)
{

    TypeParam a(0, 1, 2, 3);
    TypeParam b(4, 5, 6, 7);
    TypeParam c(8, 9, 10, 11);
    TypeParam x;
    TypeParam y;
    TypeParam z;

    VectorToScalarT<TypeParam> out_buffer1[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer2[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer3[ValuesPerPack<TypeParam>];

    Deinterleave4(a, b, c, x, y, z);

    x.store(out_buffer1);
    y.store(out_buffer2);
    z.store(out_buffer3);

    // x expected = 0,3,6,9
    ASSERT_FLOAT_EQ(out_buffer1[0], 0);
    ASSERT_FLOAT_EQ(out_buffer1[1], 3);
    ASSERT_FLOAT_EQ(out_buffer1[2], 6);
    ASSERT_FLOAT_EQ(out_buffer1[3], 9);

    // y expected = 1,4,7,10
    ASSERT_FLOAT_EQ(out_buffer2[0], 1);
    ASSERT_FLOAT_EQ(out_buffer2[1], 4);
    ASSERT_FLOAT_EQ(out_buffer2[2], 7);
    ASSERT_FLOAT_EQ(out_buffer2[3], 10);

    // z expected = 2,5,8,11
    ASSERT_FLOAT_EQ(out_buffer3[0], 2);
    ASSERT_FLOAT_EQ(out_buffer3[1], 5);
    ASSERT_FLOAT_EQ(out_buffer3[2], 8);
    ASSERT_FLOAT_EQ(out_buffer3[3], 11);
    
}


template <typename T>
class Deinterleave8Test : public ::testing::Test
{
public:
    // blank, we do all the stuff in each test
};

TYPED_TEST_SUITE(Deinterleave8Test, Width8Implementations);

TYPED_TEST(Deinterleave8Test, Deinterleave)
{

    TypeParam a(0, 1, 2, 3, 4, 5, 6, 7);
    TypeParam b(8, 9, 10, 11, 12, 13, 14, 15);
    TypeParam c(16, 17, 18, 19, 20, 21, 22, 23);
    TypeParam x;
    TypeParam y;
    TypeParam z;

    VectorToScalarT<TypeParam> out_buffer1[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer2[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> out_buffer3[ValuesPerPack<TypeParam>];

    Deinterleave8(a, b, c, x, y, z);

    x.store(out_buffer1);
    y.store(out_buffer2);
    z.store(out_buffer3);

    // x expected = 0,3,6,9,12,15,18,21
    ASSERT_FLOAT_EQ(out_buffer1[0], 0);
    ASSERT_FLOAT_EQ(out_buffer1[1], 3);
    ASSERT_FLOAT_EQ(out_buffer1[2], 6);
    ASSERT_FLOAT_EQ(out_buffer1[3], 9);
    ASSERT_FLOAT_EQ(out_buffer1[4], 12);
    ASSERT_FLOAT_EQ(out_buffer1[5], 15);
    ASSERT_FLOAT_EQ(out_buffer1[6], 18);
    ASSERT_FLOAT_EQ(out_buffer1[7], 21);

    // y expected = 1,4,7,10,13,16,19,22
    ASSERT_FLOAT_EQ(out_buffer2[0], 1);
    ASSERT_FLOAT_EQ(out_buffer2[1], 4);
    ASSERT_FLOAT_EQ(out_buffer2[2], 7);
    ASSERT_FLOAT_EQ(out_buffer2[3], 10);
    ASSERT_FLOAT_EQ(out_buffer2[4], 13);
    ASSERT_FLOAT_EQ(out_buffer2[5], 16);
    ASSERT_FLOAT_EQ(out_buffer2[6], 19);
    ASSERT_FLOAT_EQ(out_buffer2[7], 22);

    // y expected = 2,5,8,11,14,17,20,23
    ASSERT_FLOAT_EQ(out_buffer3[0], 2);
    ASSERT_FLOAT_EQ(out_buffer3[1], 5);
    ASSERT_FLOAT_EQ(out_buffer3[2], 8);
    ASSERT_FLOAT_EQ(out_buffer3[3], 11);
    ASSERT_FLOAT_EQ(out_buffer3[4], 14);
    ASSERT_FLOAT_EQ(out_buffer3[5], 17);
    ASSERT_FLOAT_EQ(out_buffer3[6], 20);
    ASSERT_FLOAT_EQ(out_buffer3[7], 23);
    
}