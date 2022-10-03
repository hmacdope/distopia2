#ifndef DISTOPIA_DISPATCH_HELPERS_H
#define DISTOPIA_DISPATCH_HELPERS_H


typedef void CalcBondsOrthoFT(const float *coords0, const float *coords1,
                              const float *box, std::size_t n, float *out);

typedef void CalcBondsOrthoDT(const double *coords0, const double *coords1,
                              const double *box, std::size_t n, double *out);


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


#endif 