#if DISTOPIA_DISPATCH // active only if we compile for dispatch
#if DISTOPIA_USE_SSE1 // only in lowest SIMD version

#include "simd_dispatch.h"
#include "../../vcl2/vectorclass.h"
#include "../../vcl2/instrset.h"
#include "../include/distopia.h"

#include <cstddef>
#include <iostream>

typedef void CalcBondsOrthoFT(const float *coords0, const float *coords1,
                              const float *box, std::size_t n, float *out);

typedef void CalcBondsOrthoDT(const double *coords0, const double *coords1,
                              const double *box, std::size_t n, double *out);

CalcBondsOrthoFT CalcBondsOrtho, CalcBondsOrthoDispatchF;
CalcBondsOrthoDT CalcBondsOrtho, CalcBondsOrthoDispatchD;

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
void CalcBondsOrthoDispatchF(const float *coords0, const float *coords1,
                            const float *box, std::size_t n, float *out)
{
    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:
    if (iset >= 9)
    {
        printf("\nRuntime dispatch AVX512\n");
        CalcBondsOrthoF_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
    }
    else if (iset >= 8)
    {
        printf("\nRuntime dispatch AVX2\n");
        CalcBondsOrthoF_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
    }
    else if (iset >= 7)
    {
        printf("\nRuntime dispatch AVX\n");
        CalcBondsOrthoF_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
    }
    else if (iset >= 6)
    {
        printf("\nRuntime dispatch SSE4.2\n");
        CalcBondsOrthoF_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
    }
    else if (iset >= 5)
    {
        printf("\nRuntime dispatch SSE4.1\n");
        CalcBondsOrthoF_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
    }
    else if (iset >= 4)
    {
        printf("\nRuntime dispatch SSSE3\n");
        CalcBondsOrthoF_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
    }
    else if (iset >= 3)
    {
        printf("\nRuntime dispatch SSE3\n");
        CalcBondsOrthoF_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
    }
    else if (iset >= 2)
    {
        printf("\nRuntime dispatch SSE2\n");
        CalcBondsOrthoF_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
    }
    else if (iset >= 1)
    {
        printf("\nRuntime dispatch SSE1\n");
        CalcBondsOrthoF_pointer = &Ns_SSE1::CalcBondsOrtho; // SSE1
    }
    else
    {
        // Error: lowest instruction set not supported.
        std::cerr << "Error: Minimum instruction set SSE1 not supported on this computer";
    }
    // continue in the dispatched version of the entry function
    (*CalcBondsOrthoF_pointer)(coords0, coords1, box, n, out);
}


// Dispatch function
void CalcBondsOrthoDispatchD(const double *coords0, const double *coords1,
                    const double *box, std::size_t n, double *out)
{
    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:
    if (iset >= 9)
    {
        printf("\nRuntime dispatch AVX512\n");
        CalcBondsOrthoD_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
    }
    else if (iset >= 8)
    {
        printf("\nRuntime dispatch AVX2\n");
        CalcBondsOrthoD_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
    }
    else if (iset >= 7)
    {
        printf("\nRuntime dispatch AVX\n");
        CalcBondsOrthoD_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
    }
    else if (iset >= 6)
    {
        printf("\nRuntime dispatch SSE4.2\n");
        CalcBondsOrthoD_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
    }
    else if (iset >= 5)
    {
        printf("\nRuntime dispatch SSE4.1\n");
        CalcBondsOrthoD_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
    }
    else if (iset >= 4)
    {
        printf("\nRuntime dispatch SSSE3\n");
        CalcBondsOrthoD_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
    }
    else if (iset >= 3)
    {
        printf("\nRuntime dispatch SSE3\n");
        CalcBondsOrthoD_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
    }
    else if (iset >= 2)
    {
        printf("\nRuntime dispatch SSE2\n");
        CalcBondsOrthoD_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
    }
    else if (iset >= 1)
    {
        printf("\nRuntime dispatch SSE1\n");
        CalcBondsOrthoD_pointer = &Ns_SSE1::CalcBondsOrtho; // SSE1
    }
    else
    {
        // Error: lowest instruction set not supported.
        std::cerr << "Error: Minimum instruction set SSE1 not supported on this computer";
    }
    // continue in the dispatched version of the entry function
    (*CalcBondsOrthoD_pointer)(coords0, coords1, box, n, out);
}

// Call the entry function through the function pointer.
// The first time this function is called, it goes through the dispatcher.
// The dispatcher will change the function pointer so that all subsequent
// calls go directly to the optimal version of the entry function

template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);

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

// explicitly instantiate 
template void CalcBondsOrtho<float>(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out);
template void CalcBondsOrtho<double>(const double *coords0, const double *coords1,
                    const double *box, std::size_t n, double *out);


#endif // DISTOPIA_USE_SSE1
#endif // DISTOPIA_DISPATCH