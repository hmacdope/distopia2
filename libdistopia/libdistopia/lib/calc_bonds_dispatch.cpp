#if DISTOPIA_DISPATCH // active only if we compile for dispatch
#if DISTOPIA_USE_SSE1 // only in lowest SIMD version

#define DEBUG_DISPATCH 0

#include "../include/distopia.h"
#include "simd_dispatch.h"
#include "vectorclass.h"

#include <cstddef>
#include <iostream>

typedef void CalcBondsOrthoFT(const float *coords0, const float *coords1,
                              const float *box, std::size_t n, float *out);

typedef void CalcBondsOrthoDT(const double *coords0, const double *coords1,
                              const double *box, std::size_t n, double *out);

CalcBondsOrthoFT CalcBondsOrtho, CalcBondsOrthoDispatchF;
CalcBondsOrthoDT CalcBondsOrtho, CalcBondsOrthoDispatchD;

// global simd config

constexpr simd_config _SIMD_config = simd_config();

// Define function prototypes have to manually define them until I find a way to
// typedef a templated function (possibly with decltype?)
namespace Ns_SSE1
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

namespace Ns_SSE2
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

namespace Ns_SSE3
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

namespace Ns_SSSE3
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

namespace Ns_SSE4_1
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

namespace Ns_SSE4_2
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

namespace Ns_AVX
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};
namespace Ns_AVX2
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};
namespace Ns_AVX512
{
    template <typename T>
    void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                        std::size_t n, T *out);
    template <typename T>
    void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                           std::size_t n, T *out);
    template <typename T>
    void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                           T *out);

};

CalcBondsOrthoFT *CalcBondsOrthoF_pointer = &CalcBondsOrthoDispatchF; // function pointer
CalcBondsOrthoDT *CalcBondsOrthoD_pointer = &CalcBondsOrthoDispatchD; // function pointer

// Dispatch function
// branches are on _SIMD_config are constexpr so should be trimmed nicely
// by the compiler
void CalcBondsOrthoDispatchF(const float *coords0, const float *coords1,
                             const float *box, std::size_t n, float *out)
{
#if DEBUG_DISPATCH
    printf("function dispatch: float\n");
    printf("SIMD AVX512 %i\n", _SIMD_config.has_AVX512);
    printf("SIMD AVX2 %i\n", _SIMD_config.has_AVX2);
    printf("SIMD AVX %i\n", _SIMD_config.has_AVX);
    printf("SIMD SSE4_2 %i\n", _SIMD_config.has_SSE4_2);
    printf("SIMD SSE4_1%i\n", _SIMD_config.has_SSE4_1);
    printf("SIMD SSSE3 %i\n", _SIMD_config.has_SSSE3);
    printf("SIMD SSE3 %i\n", _SIMD_config.has_SSE3);
    printf("SIMD SSE2 %i\n", _SIMD_config.has_SSE1);
    printf("SIMD SSE1 %i\n", _SIMD_config.has_SSE1);
#endif

    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:

#if DEBUG_DISPATCH
    printf("ISET: %i\n", iset);
#endif

    if (iset >= 9 && _SIMD_config.has_AVX512)
    {
#if DISTOPIA_AVX512_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
#endif
    }
    else if (iset >= 8 && _SIMD_config.has_AVX2)
    {
#if DISTOPIA_AVX2_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
#endif
    }
    else if (iset >= 7 && _SIMD_config.has_AVX)
    {
#if DISTOPIA_AVX_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
#endif
    }
    else if (iset >= 6 && _SIMD_config.has_SSE4_2)
    {
#if DISTOPIA_SSE4_2_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
#endif
    }
    else if (iset >= 5 && _SIMD_config.has_SSE4_1)
    {
#if DISTOPIA_SSE4_1_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
#endif
    }
    else if (iset >= 4 && _SIMD_config.has_SSSE3)
    {
#if DISTOPIA_SSSE3_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
#endif
    }
    else if (iset >= 3 && _SIMD_config.has_SSE3)
    {
#if DISTOPIA_SSE3_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
#endif
    }
    else if (iset >= 2 && _SIMD_config.has_SSE2)
    {
#if DISTOPIA_SSE2_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
#endif
    }
    else if (iset >= 1 && _SIMD_config.has_SSE1)
    {
// this should always be the case
#if DISTOPIA_SSE1_AVAILABLE
        CalcBondsOrthoF_pointer = &Ns_SSE1::CalcBondsOrtho; // SSE1
#endif
    }
    // continue in the dispatched version of the entry function
    (*CalcBondsOrthoF_pointer)(coords0, coords1, box, n, out);
}

// Dispatch function
void CalcBondsOrthoDispatchD(const double *coords0, const double *coords1,
                             const double *box, std::size_t n, double *out)
{
#if DEBUG_DISPATCH
    printf("function dispatch: double\n");
    printf("SIMD AVX512 %i\n", _SIMD_config.has_AVX512);
    printf("SIMD AVX2 %i\n", _SIMD_config.has_AVX2);
    printf("SIMD AVX %i\n", _SIMD_config.has_AVX);
    printf("SIMD SSE4_2 %i\n", _SIMD_config.has_SSE4_2);
    printf("SIMD SSE4_1%i\n", _SIMD_config.has_SSE4_1);
    printf("SIMD SSSE3 %i\n", _SIMD_config.has_SSSE3);
    printf("SIMD SSE3 %i\n", _SIMD_config.has_SSE3);
    printf("SIMD SSE2 %i\n", _SIMD_config.has_SSE1);
    printf("SIMD SSE1 %i\n", _SIMD_config.has_SSE1);
#endif

    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:

#if DEBUG_DISPATCH
    printf("ISET: %i", iset);
#endif

    if ((iset >= 9) && (_SIMD_config.has_AVX512))
    {
#if DISTOPIA_AVX512_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
#endif
    }
    else if ((iset >= 8) && (_SIMD_config.has_AVX2))
    {
#if DISTOPIA_AVX2_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
#endif
    }
    else if ((iset >= 7) && (_SIMD_config.has_AVX))
    {
#if DISTOPIA_AVX_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
#endif
    }
    else if ((iset >= 6) && (_SIMD_config.has_SSE4_2))
    {
#if DISTOPIA_SSE4_2_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
#endif
    }
    else if ((iset >= 5) && (_SIMD_config.has_SSE4_1))
    {
#if DISTOPIA_SSE4_1_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
#endif
    }
    else if ((iset >= 4) && (_SIMD_config.has_SSSE3))
    {
#if DISTOPIA_SSSE3_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
#endif
    }
    else if ((iset >= 3) && (_SIMD_config.has_SSE3))
    {
#if DISTOPIA_SSE3_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
#endif
    }
    else if ((iset >= 2) && (_SIMD_config.has_SSE2))
    {
#if DISTOPIA_SSE2_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
#endif
    }
    else if ((iset >= 1) && (_SIMD_config.has_SSE1))
    {
// this should always be the case
#if DISTOPIA_SSE1_AVAILABLE
        CalcBondsOrthoD_pointer = &Ns_SSE1::CalcBondsOrtho; // SSE1
#endif
    }
    // continue in the dispatched version of the entry function
    (*CalcBondsOrthoD_pointer)(coords0, coords1, box, n, out);
}

// Call the entry function through the function pointer. This is a specialisation
// of the template in /include/distopia.h

// The first time this function is called, it goes through the dispatcher.
// The dispatcher will change the function pointer so that all subsequent
// calls go directly to the optimal version of the entry function
template <>
void CalcBondsOrtho(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out)
{
    (*CalcBondsOrthoF_pointer)(coords0, coords1, box, n, out); // go to dispatched version
}

template <>
void CalcBondsOrtho(const double *coords0, const double *coords1,
                    const double *box, std::size_t n, double *out)
{
    (*CalcBondsOrthoD_pointer)(coords0, coords1, box, n, out); // go to dispatched version
}

#endif // DISTOPIA_USE_SSE1
#endif // DISTOPIA_DISPATCH