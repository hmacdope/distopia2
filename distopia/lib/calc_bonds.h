#ifndef DISTOPIA_CALC_BONDS_H
#define DISTOPIA_CALC_BONDS_H

#include "box.h"
#include "distances.h"
#include "../include/distopia.h"
#include "distopia_type_traits.h"
#include "util.h"
#include "vectorclass.h"
#include "vector_triple.h"

namespace
{

    template <typename VectorT, typename BoxT>
    void CalcBondsInner(const VectorToScalarT<VectorT> *coords0,
                        const VectorToScalarT<VectorT> *coords1,
                        const VectorToScalarT<VectorT> *box, std::size_t n,
                        VectorToScalarT<VectorT> *out)
    {
        auto vecbox = BoxT(box);
        VectorTriple<VectorT> c0{}, c1{};
        std::size_t i = 0;
        if (n % ValuesPerPack<VectorT>)
        {
            c0.load_and_deinterleave(coords0);
            c1.load_and_deinterleave(coords1);
            VectorT result = PBC_Distance(c0, c1, vecbox);
            result.store(out);
            i += n % ValuesPerPack<VectorT>;
        }
        for (; i < n; i += ValuesPerPack<VectorT>)
        {
            c0.load_and_deinterleave(&coords0[3 * i]);
            c1.load_and_deinterleave(&coords1[3 * i]);

            VectorT result = PBC_Distance(c0, c1, vecbox);
            result.store(out);
        }
    }

}

template <>
void CalcBondsOrtho(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out)
{
    CalcBondsInner<Vec16f, OrthogonalBox<Vec16f>>(coords0, coords1, box, n, out);
}
template <>
void CalcBondsOrtho(const double *coords0, const double *coords1,
                    const double *box, std::size_t n, double *out)
{
    CalcBondsInner<Vec8d, OrthogonalBox<Vec8d>>(coords0, coords1, box, n, out);
}

template <>
void CalcBondsNoBox(const float *coords0, const float *coords1, std::size_t n, float *out)
{
    CalcBondsInner<Vec16f, NoBox<Vec16f>>(coords0, coords1, nullptr, n, out);
}

template <>
void CalcBondsNoBox(const double *coords0, const double *coords1, std::size_t n, double *out)
{
    CalcBondsInner<Vec8d, NoBox<Vec8d>>(coords0, coords1, nullptr,  n, out);
}

#endif // DISTOPIA_CALC_BONDS_H