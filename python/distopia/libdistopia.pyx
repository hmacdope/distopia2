# distutils: language = c++

cimport cython
import numpy as np
cimport numpy as cnp
cnp.import_array()

cdef extern from "distopia.h" nogil:
    void CalcBondsOrtho[T](const T * coords0,
                           const T * coords1,
                           const T * box,
                           size_t n,
                           T * output)

    void CalcBondsNoBox[T](const T * coords0,
                           const T * coords1,
                           size_t n,
                           T * output)

    void CalcBondsIdxOrtho[T](const T * coords,
                              const size_t * idxs,
                              const T * box,
                              size_t n, T * out)

    void CalcBondsIdxNoBox[T](const T * coords,
                              const size_t * idxs,
                              size_t n, T * out)

@cython.boundscheck(False)
@cython.wraparound(False) 
cpdef cnp.ndarray[cnp.float32_t, ndim= 1] calc_bonds_ortho_float(float[:, ::1] coords1,
                                                                  float[:, ::1] coords2,
                                                                  float[::1] box):
    """Calculate pairwise distances between coords1 and coords2

    Parameters
    ----------
    coords1, coords2 : float32 array
      must be same length
    box : float32 array
      periodic boundary dimensions

    Returns
    -------
    distances : float32 array
      same size as coords1/2
    """
    cdef float[::1] results_view
    cdef size_t nvals = coords1.shape[0]
    cdef cnp.ndarray[cnp.float32_t, ndim= 1] results = np.empty(nvals, dtype=np.float32)
    
    results_view = results

    CalcBondsOrtho(& coords1[0][0], & coords2[0][0], & box[0], nvals, & results_view[0])

    return results

@cython.boundscheck(False)
@cython.wraparound(False) 
cpdef cnp.ndarray[cnp.float64_t, ndim= 1] calc_bonds_ortho_double(double[:, ::1] coords1,
                                                                   double[:, ::1] coords2,
                                                                   double[::1] box):
    """Calculate pairwise distances between coords1 and coords2

    Parameters
    ----------
    coords1, coords2 : float64 array
      must be same length
    box : float64 array
      periodic boundary dimensions

    Returns
    -------
    distances : float64 array
      same size as coords1/2
    """
    cdef double[::1] results_view
    cdef size_t nvals = coords1.shape[0]
    cdef cnp.ndarray[cnp.float64_t, ndim= 1] results = np.empty(nvals, dtype=np.float64)

    results_view = results

    CalcBondsOrtho(& coords1[0][0], & coords2[0][0], & box[0], nvals, & results_view[0])

    return results

@cython.boundscheck(False)
@cython.wraparound(False) 
cpdef cnp.ndarray[cnp.float32_t, ndim= 1] calc_bonds_no_box_float(float[:, ::1] coords1,
                                                                   float[:, ::1] coords2,
                                                                   float[::1] box):
    """Calculate pairwise distances between coords1 and coords2

    Parameters
    ----------
    coords1, coords2 : float32 array
      must be same length

    Returns
    -------
    distances : float32 array
      same size as coords1/2
    """
    cdef float[::1] results_view
    cdef size_t nvals = coords1.shape[0]
    cdef cnp.ndarray[cnp.float32_t, ndim= 1] results = np.empty(nvals, dtype=np.float32)

    results_view = results

    CalcBondsNoBox(& coords1[0][0], & coords2[0][0], nvals, & results_view[0])

    return results

@cython.boundscheck(False)
@cython.wraparound(False) 
cpdef cnp.ndarray[cnp.float64_t, ndim= 1] calc_bonds_no_box_double(double[:, ::1] coords1,
                                                                    double[:, ::1] coords2,
                                                                    double[::1] box):
    """Calculate pairwise distances between coords1 and coords2

    Parameters
    ----------
    coords1, coords2 : float64 array
      must be same length
    box : float64 array
      periodic boundary dimensions

    Returns
    -------
    distances : float64 array
      same size as coords1/2
    """
    cdef double[::1] results_view
    cdef size_t nvals = coords1.shape[0]
    cdef cnp.ndarray[cnp.float64_t, ndim= 1] results = np.empty(nvals, dtype=np.float64)
    results_view = results

    CalcBondsNoBox(& coords1[0][0], & coords2[0][0], nvals, & results_view[0])

    return results

@cython.boundscheck(False)
@cython.wraparound(False) 
cpdef cnp.ndarray[cnp.float32_t, ndim= 1] calc_bonds_idx_ortho_float(float[:, ::1] coords1,
                                                                    float[:, ::1] coords2,
                                                                    float[::1] box):
    """Calculate pairwise distances between coords1 and coords2

    Parameters
    ----------
    coords1, coords2 : float64 array
      must be same length
    box : float64 array
      periodic boundary dimensions

    Returns
    -------
    distances : float64 array
      same size as coords1/2
    """
    cdef float[::1] results_view
    cdef size_t nvals = coords1.shape[0]
    cdef cnp.ndarray[cnp.float32_t, ndim= 1] results = np.empty(nvals, dtype=np.float64)

    results_view = results

    CalcBondsNoBox(& coords1[0][0], & coords2[0][0], nvals, & results_view[0])

    return results

