#define N 32

#pragma once
typedef struct dplan{
  double * y; //input
  double * dy; //output
  fftw_plan p[2]; //plans for transforming
  double b; //boundary condition
} dplan;

void mkwi();

void plddx(dplan *d);
void plint(dplan *d);
void exddx(dplan *d);
void exddxl(dplan *d);
void exint(dplan *d);
