#ifdef DISTOPIA_DISPATCH // active only if we compile for dispatch

#include "simd_dispatch.h"
#include "../include/distopia.h"
#include "vectorclass.h"

#include <cstddef>

typedef float CalcBondsType(float const[]);

// function prototypes for entry function and dispatcher, defined outside namespace
CalcBondsType myfunc, myfunc_dispatch;

/******************************************************************************
                             Dispatched code
Everything in this section is compiled multiple times, with one version for
each instruction set. Speed-critical vector code belongs here.
******************************************************************************/

// Enclose all multiversion code in the chosen namespace
namespace DISPATCHED_NAMESPACE
{

    // This section may contain vectors, functions, classes, objects, etc.

    class MyClass
    { // Just a silly example
    public:
        float sum(float const f[])
        {                             // This function adds 16 floats
            Vec16f a;                 // Vector of 16 floats
            a.load(f);                // Load array into vector
            return horizontal_add(a); // Return sum of 16 elements
        }
    };

    // -----------------------------------------------------------------------------
    //                       Entry function
    // -----------------------------------------------------------------------------
    // This is the entry function that is accessed through the dispatcher.
    // This serves as the interface between the common code and the dispatched code.
    // The entry function cannot be member of a class.
    // The entry function must use arrays rather than vectors for input and output.
    float myfunc(float const f[])
    {
        MyClass myObject;
        return myObject.sum(f);
    }
}

#if INSTRSET == 2
// The common code is only included in the lowest of the compiled versions

// ---------------------------------------------------------------------------------
//                       Dispatcher
// ---------------------------------------------------------------------------------
// This function pointer initially points to the dispatcher.
// After the first call, it points to the selected version of the entry function
MyFuncType *myfunc_pointer = &myfunc_dispatch; // function pointer

// Dispatch function
float myfunc_dispatch(float const f[])
{
    int iset = instrset_detect(); // Detect supported instruction set
    // Choose which version of the entry function we want to point to:
    if (iset >= 9)
        myfunc_pointer = &Ns_AVX512::myfunc; // AVX512
    else if (iset >= 8)
        myfunc_pointer = &Ns_AVX2::myfunc; // AVX2
    else if (iset >= 7)
        myfunc_pointer = &Ns_AVX::myfunc; // AVX
    else if (iset >= 6)
        myfunc_pointer = &Ns_SSE4_2::myfunc; // SSE4.2
    else if (iset >= 5)
        myfunc_pointer = &Ns_SSE4_1::myfunc; // SSE4.1
    else if (iset >= 4)
        myfunc_pointer = &Ns_SSSE3::myfunc; // SSSE3
    else if (iset >= 3)
        myfunc_pointer = &Ns_SSE3::myfunc; // SSE3
    else if (iset >= 2)
        myfunc_pointer = &Ns_SSE2::myfunc; // SSE2
    else
    {
        // Error: lowest instruction set not supported.
        // Put any appropriate error handler here
        fprintf(stderr, "\nError: Instruction set SSE2 not supported on this computer");
        return 0.f;
    }
    // continue in the dispatched version of the entry function
    return (*myfunc_pointer)(f);
}

// Call the entry function through the function pointer.
// The first time this function is called, it goes through the dispatcher.
// The dispatcher will change the function pointer so that all subsequent
// calls go directly to the optimal version of the entry function
inline float myfunc(float const f[])
{
    return (*myfunc_pointer)(f); // go to dispatched version
}
#endif // INSTRSET == 2

#endif // DISTOPIA_DISPATCH