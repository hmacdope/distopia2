#ifndef DISTOPIA_SIMD_DISPATCH_H
#define DISTOPIA_SIMD_DISPATCH_H

#ifdef DISTOPIA_DISPATCH // active only if we compile for dispatch

#include "vectorclass.h"

// Choose namespace name depending on which instruction set we compile for.

/* The different instruction sets are defined in instrset_detect.cpp:
2:  SSE2
3:  SSE3
4:  SSSE3 (Supplementary SSE3)
5:  SSE4.1
6:  SSE4.2
7:  AVX
8:  AVX2
9:  AVX512F
10: AVX512VL + AVX512BW + AVX512DQ
*/

#if INSTRSET >= 9 // AVX512
#define DISPATCHED_NAMESPACE Ns_AVX512
#elif INSTRSET >= 8 // AVX2
#define DISPATCHED_NAMESPACE Ns_AVX2
#elif INSTRSET >= 7 // AVX
#define DISPATCHED_NAMESPACE Ns_AVX
#elif INSTRSET >= 6 // SSE4.2
#define DISPATCHED_NAMESPACE Ns_SSE4_2
#elif INSTRSET >= 5 // SSE4.1
#define DISPATCHED_NAMESPACE Ns_SSE4_1
#elif INSTRSET >= 4 // SSSE3
#define DISPATCHED_NAMESPACE Ns_SSSE3
#elif INSTRSET >= 3 // SSE3
#define DISPATCHED_NAMESPACE Ns_SSE3
#elif INSTRSET == 2 // SSE2
#define DISPATCHED_NAMESPACE Ns_SSE2
#else
#error Unsupported instruction set
#endif

#endif  // DISTOPIA_DISPATCH

#endif // DISTOPIA_SIMD_DISPATCH_H
