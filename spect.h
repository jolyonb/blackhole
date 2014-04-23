#ifndef SPECT_H
#define SPECT_H

#define N 47  //N.B. N+1 is the number of data points.

void spectSetup(double);

void ddxm(const double *, double *);
void intm(const double *, double *);

void rebasem(double *);
void filterm(double *);

double chebInterp(double *, double);

#endif
