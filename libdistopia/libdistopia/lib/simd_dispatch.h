#ifndef DISTOPIA_SIMD_DISPATCH_H
#define DISTOPIA_SIMD_DISPATCH_H

#if DISTOPIA_DISPATCH // active only if we compile for dispatch

// define so we can check mutual exclusivity
#ifndef DISTOPIA_USE_SSE1
#define DISTOPIA_USE_SSE1 0
#endif

#ifndef DISTOPIA_USE_SSE2
#define DISTOPIA_USE_SSE2 0
#endif

#ifndef DISTOPIA_USE_SSE3
#define DISTOPIA_USE_SSE3 0
#endif

#ifndef DISTOPIA_USE_SSSE3
#define DISTOPIA_USE_SSSE3 0
#endif

#ifndef DISTOPIA_USE_SSE4_1
#define DISTOPIA_USE_SSE4_1 0
#endif

#ifndef DISTOPIA_USE_SSE4_2
#define DISTOPIA_USE_SSE4_2 0
#endif

#ifndef DISTOPIA_USE_AVX
#define DISTOPIA_USE_AVX 0
#endif

#ifndef DISTOPIA_USE_AVX2
#define DISTOPIA_USE_AVX2 0
#endif

#ifndef DISTOPIA_USE_AVX512
#define DISTOPIA_USE_AVX512 0
#endif



// check SIMD options are  mutually exclusive
// check we dont have overlapping defines

static_assert(!DISTOPIA_USE_SSE2 || !DISTOPIA_USE_SSE1,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_SSE3 || !DISTOPIA_USE_SSE2,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_SSSE3 || !DISTOPIA_USE_SSE3,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_SSE4_1 || !DISTOPIA_USE_SSSE3,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_SSE4_2 || !DISTOPIA_USE_SSE4_1,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_AVX || !DISTOPIA_USE_SSE4_2,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_AVX2 || !DISTOPIA_USE_AVX,
              "SIMD config is not self-consistent");
static_assert(!DISTOPIA_USE_AVX512 || !DISTOPIA_USE_AVX2,
              "SIMD config is not self-consistent");


// Choose namespace name depending on which instruction set we compile for.

#if DISTOPIA_USE_SSE1
#define DISPATCHED_NAMESPACE Ns_SSE1
#endif

#if DISTOPIA_USE_SSE2
#define DISPATCHED_NAMESPACE Ns_SSE2
#endif

#if DISTOPIA_USE_SSE3
#define DISPATCHED_NAMESPACE Ns_SSE3
#endif

#if DISTOPIA_USE_SSSE3
#define DISPATCHED_NAMESPACE Ns_SSSE3
#endif

#if DISTOPIA_USE_SSE4_1
#define DISPATCHED_NAMESPACE Ns_SSE4_1
#endif

#if DISTOPIA_USE_SSE4_2
#define DISPATCHED_NAMESPACE Ns_SSE4_2
#endif

#if DISTOPIA_USE_SSE4_2
#define DISPATCHED_NAMESPACE Ns_SSE4_2
#endif


#if DISTOPIA_USE_AVX
#define DISPATCHED_NAMESPACE Ns_AVX
#endif

#if DISTOPIA_USE_AVX2
#define DISPATCHED_NAMESPACE Ns_AVX2
#endif

#if DISTOPIA_USE_AVX512
#define DISPATCHED_NAMESPACE Ns_AVX512
#endif


#endif  // DISTOPIA_DISPATCH

#endif // DISTOPIA_SIMD_DISPATCH_H
