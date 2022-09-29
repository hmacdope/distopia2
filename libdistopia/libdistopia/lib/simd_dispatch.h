#ifndef DISTOPIA_SIMD_DISPATCH_H
#define DISTOPIA_SIMD_DISPATCH_H

#include "vectorclass.h"

// Choose namespace name depending on which instruction set we compile for.

#if INSTRSET >= 9
#define DISPATCHED_NAMESPACE Ns_AVX512
#elif INSTRSET >= 8                    // AVX2
#define DISPATCHED_NAMESPACE Ns_AVX2
#elif INSTRSET >= 7                    // AVX
#define DISPATCHED_NAMESPACE Ns_AVX
#elif INSTRSET >= 6
#define DISPATCHED_NAMESPACE Ns_SSE4_2
#elif INSTRSET >= 5
#define DISPATCHED_NAMESPACE Ns_SSE4_1
#elif INSTRSET >= 4
#define DISPATCHED_NAMESPACE Ns_SSSE3
#elif INSTRSET >= 3
#define DISPATCHED_NAMESPACE Ns_SSE3
#elif INSTRSET == 2
#define DISPATCHED_NAMESPACE Ns_SSE2   // SSE2
#else
#error Unsupported instruction set
#endif
// ----------------------------------------------------------------------------


#endif // DISTOPIA_SIMD_DISPATCH_H
