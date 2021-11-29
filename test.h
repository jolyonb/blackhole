/*
 * test.h
 *
 * Header file companion to test.c
 *
 */

#ifndef TEST_H_
#define TEST_H_

#include <stdio.h> // File IO
#include <math.h> // Math!
#include <fftw3.h> // Fastest fourier transform in the west
#include <string.h> // Used for reading the parameter file
#include <gsl/gsl_spline.h> // Used for interpolating to obtain initial data on the null slice
#include <gsl/gsl_errno.h> // Needed for GSL stuff
#include "misner-sharp.h" // Routines for evolution of the Misner-Sharp

// Data type for describing a spline
typedef struct splinetool {
	gsl_interp_accel *acc;
	gsl_spline *spline;
} spline;

// Gridded values of A from 0 to 1
static double A[N+1];

// Prints out current data
void printstate(state data, FILE*);

// Reads parameters from the parameter file
double getparam(const char *parameter);
int getintparam(const char *parameter);

// Prints out initial data on the null slice (A, u, m, r, t)
void printnullinitdata(state data, FILE*);

// Dumps an array to disc for debug purposes
void dumparray(double *, int num, const char *filename);

// Constructs initial data on the null slice
void constructnulldata(double umrat[][5], int, state *);

// Prints out data on the null geodesic
void printgeodesicdata(double umrat[][5], int, FILE*);

#endif /* TEST_H_ */
