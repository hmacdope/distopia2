
#include "vectorclass.h"

void saxpy(const float aval, const float bval)
{

    float a[16], b[16], c[16];
    for (char i = 0; i < 16; i++)
    {
        a[i] = aval;
        b[i] = bval;
    }

    Vec16f avec, bvec, cvec;
    avec.load(a);
    bvec.load(b);
    cvec = avec + bvec * 1.5f;
    cvec.store(c);

    for (char i = 0; i < 16; i++)
    {
        printf(" %f", c[i]);
    }
}