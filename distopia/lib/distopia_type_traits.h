#ifndef DISTOPIA_TYPE_TRAITS_H
#define DISTOPIA_TYPE_TRAITS_H

#include "vectorclass.h"

template <typename VectorT>
struct VectorToScalarTStruct;
// map each scalar to matching scalar type
template <>
struct VectorToScalarTStruct<float>
{
    using type = float;
};
template <>
struct VectorToScalarTStruct<double>
{
    using type = double;
};
// map each vector to matching scalar type
template <>
struct VectorToScalarTStruct<Vec4f>
{
    using type = float;
};
template <>
struct VectorToScalarTStruct<Vec2d>
{
    using type = double;
};
template <>
struct VectorToScalarTStruct<Vec8f>
{
    using type = float;
};
template <>
struct VectorToScalarTStruct<Vec4d>
{
    using type = double;
};
template <>
struct VectorToScalarTStruct<Vec16f>
{
    using type = float;
};
template <>
struct VectorToScalarTStruct<Vec8d>
{
    using type = double;
};

template <typename VectorT>
using VectorToScalarT = typename VectorToScalarTStruct<VectorT>::type;

template <typename T>
constexpr std::size_t ValuesPerPack = sizeof(T) / sizeof(VectorToScalarT<T>);

#endif // DISTOPIA_TYPE_TRAITS_H