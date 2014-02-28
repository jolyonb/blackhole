#ifndef SPECT_H
#define SPECT_H

#define N 32  //N.B. N+1 is the number of data points.

void spectSetup(double);

void ddxm(const double *, double *);
void intm(const double *, double *);

void rebasem(double *);

#endif
