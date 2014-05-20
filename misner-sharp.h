
#ifndef MISNER_SHARP_H
#define MISNER_SHARP_H

#include "spect.h"

// Dynamic variables
typedef struct dynvar {
    double u[N+1];//New u = U/R
    double m[N+1];//New m= m/R^2
    double r[N+1];
    double photon; // Location of photon: 0 to 1 between A0 and AFRW
} dynvar;

// Rest of the variables: gamma squared, rho, phi, r', rho'
typedef struct resvar {
    double gamma2[N+1];
    double rho[N+1];
    double phi[N+1];
    double dr[N+1];
    double drho[N+1];
    double lastupdated; // Time that the update call was last run
} resvar;

// Everything together now!
typedef struct state {
    //variables to track
    dynvar umr; // Dynamic variables
    resvar res; // The rest

    double t; // Time
} state;

// Pi/3. Because.
#define M_PI_3 1.0471975511965977462

// Value of R at the boundary at the initial time
// Ie, size of the domain
extern double AFRW;

//regridding ratio
extern double RATIO;

//Value of A[0]. becomes != 0 after regridding
extern double A0;

void msInit(state *s);
void msRelease();
void msSetup(double a);
int msEvolve(state *s, double t1, double *umrat);

#endif
