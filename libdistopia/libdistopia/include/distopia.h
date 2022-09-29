#ifndef DISTOPIA_H
#define DISTOPIA_H

#include <cstddef>

#ifdef DISTOPIA_DISPATCH
#include "simd_dispatch.h"
#endif


#ifdef DISTOPIA_DISPATCH
namespace DISPATCHED_NAMESPACE
{
#endif

/*! \file 
    \brief Main public header for distopia
    
    Contains functions to calculate distances, angles and dihedrals that
    efficently leverage SIMD 
*/


/*!
    \brief     Calculates the distance between two sets of points in two
               contiguous arrays under orthorhombic periodic boundary
               conditions.
    \tparam    T the type of the coordinates (float or double)
    \param     coords0 array of coordinates
    \param     coords1 array of coordinates
    \param     box the bounding box of the simulation
    \param     n the number of distances to calculate
    \param     out result array into which the distances are returned
*/
template <typename T>
void CalcBondsOrtho(const T *coords0, const T *coords1, const T *box,
                    std::size_t n, T *out);

/*!
    \brief     Calculates the distance between two sets of points in two
               contiguous arrays without periodic boundary conditions
    \tparam    T the type of the coordinates (float or double)
    \param     coords0 array of coordinates
    \param     coords1 array of coordinates
    \param     n the number of distances to calculate
    \param     out result array into which the distances are returned
*/
template <typename T>
void CalcBondsNoBox(const T *coords0, const T *coords1, std::size_t n, T *out);

/*!
    \brief     Calculates the distance between sets of two points in a single
               array indexed by the idxs parameter under orthorhombic periodic
               boundary conditions
    \tparam    T the type of the coordinates (float or double)
    \param     coords array of coordinates
    \param     idxs the indicies of the distances to calculate
    \param     box the bounding box of the simulation
    \param     n the number of distances to calculate
    \param     out result array into which the distances are returned
*/
template <typename T>
void CalcBondsIdxOrtho(const T *coords, const std::size_t *idxs, const T *box,
                       std::size_t n, T *out);

/*!
    \brief     Calculates the distance between sets of two points in a single
               array indexed by the idxs parameter without periodic boundary
               conditions
    \tparam    T the type of the coordinates (float or double)
    \param     coords array of coordinates
    \param     idxs the indicies of the distances to calculate
    \param     n the number of distances to calculate
    \param     out result array into which the distances are returned
*/
template <typename T>
void CalcBondsIdxNoBox(const T *coords, const std::size_t *idxs, std::size_t n,
                       T *out);


#ifdef DISTOPIA_DISPATCH
} // DISPATCHED_NAMESPACE
#endif

#endif // DISTOPIA_H
