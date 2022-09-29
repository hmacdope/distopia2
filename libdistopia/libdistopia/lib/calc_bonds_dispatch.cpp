#ifdef DISTOPIA_DISPATCH // active only if we compile for dispatch

#include "simd_dispatch.h"
#include "../include/distopia.h"
#include "vectorclass.h"

#include <cstddef>

typedef  void CalcBondsOrthoFT(const float *coords0, const float *coords1,
                    const float *box, std::size_t n, float *out);


// Define function prototypes for each version
namespace Ns_SSE2{     // SSE2 instruction set
    CalcBondsOrthoFT CalcBondsOrtho;
};
namespace Ns_AVX{      // AVX instruction set
    CalcBondsOrthoFT myfunc;
};
namespace Ns_AVX2{     // AVX2 instruction set
    CalcBondsOrthoFT myfunc;
};
namespace Ns_AVX512{   // AVX512 instruction set
    CalcBondsOrthoFT myfunc;
};

// function prototypes for entry function and dispatcher, defined outside namespace
CalcBondsOrthoFT CalcBondsOrthoF, CalcBondsOrthoFDispatch;

CalcBondsOrthoDT CalcBondsOrthoD, CalcBondsOrthoDDispatch;

/******************************************************************************
                             Dispatched code
Everything in this section is compiled multiple times, with one version for
each instruction set. Speed-critical vector code belongs here.
******************************************************************************/

// Enclose all multiversion code in the chosen namespace
namespace DISPATCHED_NAMESPACE
{

//     // This section may contain vectors, functions, classes, objects, etc.

//     class MyClass
//     { // Just a silly example
//     public:
//         float sum(float const f[])
//         {                             // This function adds 16 floats
//             Vec16f a;                 // Vector of 16 floats
//             a.load(f);                // Load array into vector
//             return horizontal_add(a); // Return sum of 16 elements
//         }
//     };

//     // -----------------------------------------------------------------------------
//     //                       Entry function
//     // -----------------------------------------------------------------------------
//     // This is the entry function that is accessed through the dispatcher.
//     // This serves as the interface between the common code and the dispatched code.
//     // The entry function cannot be member of a class.
//     // The entry function must use arrays rather than vectors for input and output.
//     float myfunc(float const f[])
//     {
//         MyClass myObject;
//         return myObject.sum(f);
//     }
}

#if INSTRSET == 2
// The common code is only included in the lowest of the compiled versions

// ---------------------------------------------------------------------------------
//                       Dispatcher
// ---------------------------------------------------------------------------------
// This function pointer initially points to the dispatcher.
// After the first call, it points to the selected version of the entry function
CalcBondsOrthoFT *CalcBondsOrthoF_pointer = &CalcBondsOrthoFDispatch; // function pointer

// Dispatch function
void CalcBondsOrthoFDispatch(const float *coords0, const float *coords1,
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
    else
    {
        // Error: lowest instruction set not supported.
        // Put any appropriate error handler here
        fprintf(stderr, "\nError: Instruction set SSE2 not supported on this computer");
    }
    // continue in the dispatched version of the entry function
    *CalcBondsOrthoF_pointer(coords0, coords1, box, n, out);
}

// Call the entry function through the function pointer.
// // The first time this function is called, it goes through the dispatcher.
// // The dispatcher will change the function pointer so that all subsequent
// // calls go directly to the optimal version of the entry function
// inline float myfunc(float const f[])
// {
//     return (*myfunc_pointer)(f); // go to dispatched version
// }
#endif // INSTRSET == 2

#endif // DISTOPIA_DISPATCH