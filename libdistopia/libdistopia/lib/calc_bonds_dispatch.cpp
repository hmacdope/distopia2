#if DISTOPIA_DISPATCH // active only if we compile for dispatch
#if DISTOPIA_USE_SSE1 // only in lowest SIMD version

#include "simd_dispatch.h"
#include "vectorclass.h"

#include <cstddef>
#include <iostream>

typedef  void CalcBondsOrthoFT(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out);


CalcBondsOrthoFT  CalcBondsOrtho, CalcBondsOrthoDispatch;

// Define function prototypes
namespace Ns_SSE1{
    CalcBondsOrthoFT CalcBondsOrtho;
};

namespace Ns_SSE2{     
    CalcBondsOrthoFT CalcBondsOrtho;
};

namespace Ns_SSE3{
    CalcBondsOrthoFT CalcBondsOrtho;
};

namespace Ns_SSSE3{     
    CalcBondsOrthoFT CalcBondsOrtho;
};

namespace Ns_SSE4_1{     
    CalcBondsOrthoFT CalcBondsOrtho;
};

namespace Ns_SSE4_2{     
    CalcBondsOrthoFT CalcBondsOrtho;
};

namespace Ns_AVX{
    CalcBondsOrthoFT CalcBondsOrtho;
};
namespace Ns_AVX2{
    CalcBondsOrthoFT CalcBondsOrtho;
};
namespace Ns_AVX512{
    CalcBondsOrthoFT CalcBondsOrtho;
};

CalcBondsOrthoFT *CalcBondsOrthoF_pointer = &CalcBondsOrthoDispatch; // function pointer



// Dispatch function
void CalcBondsOrthoDispatch(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out)
{
    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:
    if (iset >= 9)
        CalcBondsOrthoF_pointer = &Ns_AVX512::CalcBondsOrtho; // AVX512
    else if (iset >= 8)
        CalcBondsOrthoF_pointer = &Ns_AVX2::CalcBondsOrtho; // AVX2
    else if (iset >= 7)
        CalcBondsOrthoF_pointer = &Ns_AVX::CalcBondsOrtho; // AVX
    else if (iset >= 6)
        CalcBondsOrthoF_pointer = &Ns_SSE4_2::CalcBondsOrtho; // SSE4.2
    else if (iset >= 5)
        CalcBondsOrthoF_pointer = &Ns_SSE4_1::CalcBondsOrtho; // SSE4.1
    else if (iset >= 4)
        CalcBondsOrthoF_pointer = &Ns_SSSE3::CalcBondsOrtho; // SSSE3
    else if (iset >= 3)
        CalcBondsOrthoF_pointer = &Ns_SSE3::CalcBondsOrtho; // SSE3
    else if (iset >= 2)
        CalcBondsOrthoF_pointer = &Ns_SSE2::CalcBondsOrtho; // SSE2
    else if (iset >= 1)
        CalcBondsOrthoF_pointer = &Ns_SSE1::CalcBondsOrtho; // SSE1
    else
    {
        // Error: lowest instruction set not supported.
        std::cerr << "Error: Instruction set SSE1 not supported on this computer";
    }
    // continue in the dispatched version of the entry function
    // *CalcBondsOrthoF_pointer(coords0, coords1, box, n, out);
}



// // Call the entry function through the function pointer.
// // // The first time this function is called, it goes through the dispatcher.
// // // The dispatcher will change the function pointer so that all subsequent
// // // calls go directly to the optimal version of the entry function
// // inline float myfunc(float const f[])
// // {
// //     return (*myfunc_pointer)(f); // go to dispatched version
// // }
// #endif // INSTRSET == 2

#endif // DISTOPIA_USE_SSE1
#endif // DISTOPIA_DISPATCH