# distutils: language = c++

import numpy as np

cdef extern from "distopia.h" nogil:
     void CalcBondsOrtho[T](const T* coords0,
                            const T* coords1,
                            const T* box,
                            size_t n,
                            T* output)
    


def calc_bonds(float[:, ::1] coords1,
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
    cdef object results
    cdef unsigned int nvals
    cdef float[::1] results_view

    nvals = coords1.shape[0]

    results = np.empty(nvals, dtype=np.float32)
    results_view = results

    CalcBondsOrtho(&coords1[0][0], &coords2[0][0], &box[0], nvals, &results_view[0])

    return results