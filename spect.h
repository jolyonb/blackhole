#ifndef SPECT_H
#define SPECT_H

#include <fftw3.h>
#define N 32

typedef struct dplan{
  double * yin; //input
  double * yout; //output
  fftw_plan p[2]; //plans for transforming
  double b; //boundary condition
} dplan;

typedef struct flyplan{
  double * y;
  fftw_plan p;
  int n;
} flyplan;

void mkwi();

void plddx(dplan *);
void plint(dplan *);
void exddx(dplan *);
void exddxl(dplan *);
void exint(dplan *);

void plfly(flyplan *);
void exfly(flyplan *,double,double);

#endif
