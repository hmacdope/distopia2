#if DISTOPIA_DISPATCH // active only if we compile for dispatch
#if DISTOPIA_USE_SSE1 // only in lowest SIMD version


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


// Define function prototypes
namespace Ns_SSE1
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

namespace Ns_SSE2
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

namespace Ns_SSE3
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

namespace Ns_SSSE3
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

namespace Ns_SSE4_1
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

namespace Ns_SSE4_2
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

namespace Ns_AVX
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};
namespace Ns_AVX2
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};
namespace Ns_AVX512
{
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);
};

CalcBondsOrthoFT *CalcBondsOrthoF_pointer = &CalcBondsOrthoDispatchF; // function pointer
CalcBondsOrthoDT *CalcBondsOrthoD_pointer = &CalcBondsOrthoDispatchD; // function pointer

// Dispatch function
// branches are on _SIMD_config are constexpr so should be trimmed nicely
// by the compiler
void CalcBondsOrthoDispatchF(const float *coords0, const float *coords1,
                            const float *box, std::size_t n, float *out)
{
    printf("function dispatch: float\n");
    printf("SIMDAVX512 %i\n",_SIMD_config.has_AVX512);
    printf("SIMDAVX2 %i\n",_SIMD_config.has_AVX2);
    printf("SIMDAVX %i\n",_SIMD_config.has_AVX);
    printf("SIMDSSE3 %i\n",_SIMD_config.has_SSE3);
    printf("SIMDSSE1 %i\n",_SIMD_config.has_SSE1);

    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:

    printf("ISET: %i\n", iset);
    if (iset >= 9 && _SIMD_config.has_AVX512)
    {
        #if DISTOPIA_AVX512_AVAILABLE
        printf("\nRuntime dispatch AVX512\n");
        CalcBondsOrthoF_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
        #endif

    }
    else if  (iset >= 8 && _SIMD_config.has_AVX2)
    {
        #if DISTOPIA_AVX2_AVAILABLE
        printf("\nRuntime dispatch AVX2\n");
        CalcBondsOrthoF_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
        #endif
    }
    else if (iset >= 7 && _SIMD_config.has_AVX)
    {
       #if DISTOPIA_AVX_AVAILABLE
        printf("\nRuntime dispatch AVX\n");
        CalcBondsOrthoF_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
       #endif
    }
    else if (iset >= 6 && _SIMD_config.has_SSE4_2)
    {
        #if DISTOPIA_SSE4_2_AVAILABLE
        printf("\nRuntime dispatch SSE4.2\n");
        CalcBondsOrthoF_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
        #endif
    }
    else if (iset >= 5 && _SIMD_config.has_SSE4_1)
    {
        #if DISTOPIA_SSE4_1_AVAILABLE
        printf("\nRuntime dispatch SSE4.1\n");
        CalcBondsOrthoF_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
        #endif
    }
    else if (iset >= 4 && _SIMD_config.has_SSSE3)
    {
        #if DISTOPIA_SSSE3_AVAILABLE
        printf("\nRuntime dispatch SSSE3\n");
        CalcBondsOrthoF_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
        #endif
    }
    else if (iset >= 3 && _SIMD_config.has_SSE3)
    {
        #if DISTOPIA_SSE3_AVAILABLE 
        printf("\nRuntime dispatch SSE3\n");
        CalcBondsOrthoF_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
        #endif
    }
    else if (iset >= 2 && _SIMD_config.has_SSE2)
    {
        #if DISTOPIA_SSE2_AVAILABLE 
        printf("\nRuntime dispatch SSE2\n");
        CalcBondsOrthoF_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
        #endif
    }
    else if (iset >= 1 && _SIMD_config.has_SSE1)
    {
        // this should always be the case
        #if DISTOPIA_SSE1_AVAILABLE
        printf("\nRuntime dispatch SSE1\n");
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
    printf("function dispatch: double\n");
    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:

    printf("ISET: %i", iset);
    if ((iset >= 9) && (_SIMD_config.has_AVX512))
    {
        #if DISTOPIA_AVX512_AVAILABLE
        printf("\nRuntime dispatch AVX512\n");
        CalcBondsOrthoD_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
        #endif

    }
    else if  ((iset >= 8) && (_SIMD_config.has_AVX2))
    {
        #if DISTOPIA_AVX2_AVAILABLE
        printf("\nRuntime dispatch AVX2\n");
        CalcBondsOrthoD_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
        #endif
    }
    else if ((iset >= 7) && (_SIMD_config.has_AVX))
    {
        #if DISTOPIA_AVX_AVAILABLE
        printf("\nRuntime dispatch AVX\n");
        CalcBondsOrthoD_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
        #endif
    }
    else if ((iset >= 6) && (_SIMD_config.has_SSE4_2))
    {
        #if DISTOPIA_SSE4_2_AVAILABLE
        printf("\nRuntime dispatch SSE4.2\n");
        CalcBondsOrthoD_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
        #endif
    }
    else if ((iset >= 5) && (_SIMD_config.has_SSE4_1))
    {
        #if DISTOPIA_SSE4_1_AVAILABLE
        printf("\nRuntime dispatch SSE4.1\n");
        CalcBondsOrthoD_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
        #endif
    }
    else if ((iset >= 4) && (_SIMD_config.has_SSSE3))
    {
        #if DISTOPIA_SSSE3_AVAILABLE
        printf("\nRuntime dispatch SSSE3\n");
        CalcBondsOrthoD_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
        #endif
    }
    else if ((iset >= 3) && (_SIMD_config.has_SSE3))
    {
        #if DISTOPIA_SSE3_AVAILABLE 
        printf("\nRuntime dispatch SSE3\n");
        CalcBondsOrthoD_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
        #endif
    }
    else if ((iset >= 2) && (_SIMD_config.has_SSE2))
    {
        #if DISTOPIA_SSE2_AVAILABLE 
        printf("\nRuntime dispatch SSE2\n");
        CalcBondsOrthoD_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
        #endif
    }
    else if ((iset >= 1) && (_SIMD_config.has_SSE1))
    {
        // this should always be the case
        #if DISTOPIA_SSE1_AVAILABLE
        printf("\nRuntime dispatch SSE1\n");
        CalcBondsOrthoD_pointer = &Ns_SSE1::CalcBondsOrtho; // SSE1
        #endif
    }
    // continue in the dispatched version of the entry function
    (*CalcBondsOrthoD_pointer)(coords0, coords1, box, n, out);
}

// Call the entry function through the function pointer.
// The first time this function is called, it goes through the dispatcher.
// The dispatcher will change the function pointer so that all subsequent
// calls go directly to the optimal version of the entry function
template <>
void CalcBondsOrtho(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out)
{
    printf("Function entry: float\n");
    (*CalcBondsOrthoF_pointer)(coords0, coords1, box, n, out); // go to dispatched version
}

template <>
void CalcBondsOrtho(const double *coords0, const double *coords1,
                    const double *box, std::size_t n, double *out)
{
    printf("Function_entry: double\n");
    (*CalcBondsOrthoD_pointer)(coords0, coords1, box, n, out); // go to dispatched version
}


#endif // DISTOPIA_USE_SSE1
#endif // DISTOPIA_DISPATCH