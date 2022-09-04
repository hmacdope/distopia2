#include <iostream>

#include "gtest/gtest.h"
#include "../lib/example.h"
#include "../lib/vector_triple.h"


using testing::Types;
typedef Types<Vec4f, Vec8f, Vec16f, Vec2d, Vec4d, Vec8d> Implementations;


template <typename T>
class VectorTripleTest : public ::testing::Test {
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

    vt.x.store(buf0);
    x.store(buf1);
    for (int i = 0; i < vt.size; i++)
    {
        ASSERT_FLOAT_EQ(buf0[i], buf1[i]);
    }
}


TYPED_TEST(VectorTripleTest, LoadFromBuffer)
{
    auto vt = VectorTriple<TypeParam>();

    VectorToScalarT<TypeParam> input_buffer[3*ValuesPerPack<TypeParam>];
    
    VectorToScalarT<TypeParam> buf0[ValuesPerPack<TypeParam>];
    VectorToScalarT<TypeParam> buf1[ValuesPerPack<TypeParam>];

    vt.x.store(buf0);
    x.store(buf1);
    for (int i = 0; i < vt.size; i++)
    {
        ASSERT_FLOAT_EQ(buf0[i], buf1[i]);
    }
}



