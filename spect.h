/*
 * Header file for all spectral manipulations
 */

#ifndef SPECT_H
#define SPECT_H

// Number of points - 1. 31 is good, as is 47, and 63.
#define N 47  //N.B. N+1 is the number of data points.

// Initialize spectral matrices
void spectSetup(double);

// Derivative and integrate methods (integrate from 0 outwards)
void ddxm(const double *, double *);
void intm(const double *, double *);
double ddxm0(const double *);

// Rebasing
void rebasem(double *);

// Filtering
void filterm(double *);

// Interpolate a chebyshev polynomial
double chebInterp(double *, double);

#endif
