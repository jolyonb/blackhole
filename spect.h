#ifndef SPECT_H
#define SPECT_H

#define N 32  //N.B. N+1 is the number of data points.

void spectSetup(double);

void ddxm(double *, double *);
void intm(double *, double *);

void rebasem(double *);

#endif
