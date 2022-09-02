
#include "vectorclass.h"


float a[8], b[8], c[8];
Vec8f avec, bvec, cvec
avec.load(a);
bvec.load(b);
cvec = avec + bvec * 1.5f;
cvec.store(c);