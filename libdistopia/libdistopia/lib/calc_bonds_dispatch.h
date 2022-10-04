#ifndef DISTOPIA_CALC_BONDS_DISPATCH_H
#define DISTOPIA_CALC_BONDS_DISPATCH_H

#include <cstdio>
#include "distopia_type_traits.h"

typedef void CalcBondsOrthoFT(const float *coords0, const float *coords1,
                              const float *box, std::size_t n, float *out);

typedef void CalcBondsOrthoDT(const double *coords0, const double *coords1,
                              const double *box, std::size_t n, double *out);

CalcBondsOrthoFT CalcBondsOrtho, CalcBondsOrthoDispatchF;
CalcBondsOrthoDT CalcBondsOrtho, CalcBondsOrthoDispatchD;

template <typename T>
void CalcBondsOrthoDispatch(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);


// need to define some types and type traits here possibly move to type traits 
// header

// function pointer types
using CalcBondsOrtho_FptrT = decltype(&CalcBondsOrthoDispatch<float>);
using CalcBondsOrtho_DptrT = decltype(&CalcBondsOrthoDispatch<double>);

// type traits 
template <typename T>
struct OrthoDispatchTypeToFptrTStruct;

template <>
struct OrthoDispatchTypeToFptrTStruct<float>
{
    using type = CalcBondsOrtho_FptrT;
};

template <>
struct OrthoDispatchTypeToFptrTStruct<double>
{
    using type = CalcBondsOrtho_DptrT;
};

template <typename T>
using OrthoDispatchTypeToFptrT = typename OrthoDispatchTypeToFptrTStruct<T>::type;


// helper holds pointers to all the functions
class function_pointer_register
{

public:
    CalcBondsOrtho_FptrT CalcBondsOrtho_Fptr;
    CalcBondsOrtho_DptrT CalcBondsOrtho_Dptr;

    function_pointer_register()
    {
        CalcBondsOrtho_Fptr = &CalcBondsOrthoDispatch<float>;
        CalcBondsOrtho_Dptr = &CalcBondsOrthoDispatch<double>;
    }

    template <int select, typename FPtrT>
    void set_ptr(FPtrT fptr)
    {
        if constexpr (select == 0)
        {
            CalcBondsOrtho_Fptr = fptr;
        }
        else if (select == 1)
        {
            CalcBondsOrtho_Dptr = fptr;
        }
    }

    template <int select>
    auto get_ptr()
    {
        if constexpr (select == 0)
        {
            return CalcBondsOrtho_Fptr;
        }

        else if (select == 1)
        {
            return CalcBondsOrtho_Dptr;
        }
    }
};

// Define function prototypes

// pretty ugly macros to avoid repeating ourselves
// NOTE still needs ; for decl

#define CalcBondsOrthoTemplate template <typename T>                  \
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box, \
                    std::size_t n, T *out)

#define CalcBondsNoBoxTemplate template <typename T> \
void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out)

#define CalcBondsIdxOrthoTemplate template <typename T>                        \
void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box, \
                       std::size_t n, T *out)

#define CalcBondsIdxNoBoxTemplate template <typename T>                         \
void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n, \
                       T *out)

namespace Ns_SSE1
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

namespace Ns_SSE2
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

namespace Ns_SSE3
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

namespace Ns_SSSE3
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

namespace Ns_SSE4_1
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

namespace Ns_SSE4_2
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

namespace Ns_AVX
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};
namespace Ns_AVX2
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;

};
namespace Ns_AVX512
{
    CalcBondsOrthoTemplate;
    CalcBondsNoBoxTemplate;
    CalcBondsIdxOrthoTemplate;
    CalcBondsIdxNoBoxTemplate;
};

#endif // DISTOPIA_CALC_BONDS_DISPATCH_H