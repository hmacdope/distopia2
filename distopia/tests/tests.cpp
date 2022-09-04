#include <numeric>
#include <iostream>

#include "gtest/gtest.h"
#include "../lib/example.h"
#include "../lib/vector_triple.h"

using testing::Types;
typedef Types<Vec4f, Vec8f, Vec16f, Vec2d, Vec4d, Vec8d> Implementations;

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

    VectorToScalarT<TypeParam> buf0[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> buf1[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> buf2[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> buf3[ValuesPerPack<TypeParam>];

    x.store(buf0);
    vt.x.store(buf1);
    vt.y.store(buf2);
    vt.z.store(buf3);

    for (int i = 0; i < vt.size; i++)
    {
        ASSERT_FLOAT_EQ(buf0[i], buf1[i]);
        ASSERT_FLOAT_EQ(buf0[i], buf2[i]);
        ASSERT_FLOAT_EQ(buf0[i], buf3[i]);
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
            ASSERT_FLOAT_EQ(input_buffer[ValuesPerPack<TypeParam> +j], out_buffer2[j]);
            ASSERT_FLOAT_EQ(input_buffer[ValuesPerPack<TypeParam>*2 +j], out_buffer3[j]);
        }
}
