#ifndef DISTOPIA_VECTOR_TRIPLE_H
#define DISTOPIA_VECTOR_TRIPLE_H

#include "distopia_type_traits.h"

template <typename VectorT>
class VectorTriple
{

public:
    using ScalarT = VectorToScalarT<VectorT>;
    // SIMD type that contains x coordinates
    VectorT x;
    // SIMD type that contains y coordinates
    VectorT y;
    // SIMD type that contains z coordinates
    VectorT z;
    // number of values per vector
    static constexpr std::size_t size = ValuesPerPack<VectorT>;

    inline VectorTriple(const VectorT a, const VectorT b, const VectorT c)
        : x(a), y(b), z(c) {}

    void load(const ScalarT *source)
    {
        VectorT t1, t2, t3;
        t1.load(source);
        t2.load(source + size);
        t3.load(source + 2 * size);
    }
};

template <typename VectorT>
inline VectorTriple<VectorT> operator+(VectorTriple<VectorT> a,
                                       VectorTriple<VectorT> b)
{
    return VectorTriple<VectorT>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename VectorT>
inline VectorTriple<VectorT> operator-(VectorTriple<VectorT> a,
                                       VectorTriple<VectorT> b)
{
    return VectorTriple<VectorT>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename VectorT>
inline VectorTriple<VectorT> operator*(VectorTriple<VectorT> a,
                                       VectorTriple<VectorT> b)
{
    return VectorTriple<VectorT>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <typename VectorT>
inline VectorTriple<VectorT> operator/(VectorTriple<VectorT> a,
                                       VectorTriple<VectorT> b)
{
    return VectorTriple<VectorT>(a.x / b.y, a.y / b.y, a.z / b.z);
}
#endif // DISTOPIA_VECTOR_TRIPLE_H