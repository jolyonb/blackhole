#define N 32

typedef struct dplan{
  double * restrict y;
  double * restrict dy;
  fftw_plan p[2];
  double b;
} dplan;

void mkwi();

void plddx(dplan *d);
void plint(dplan *d);
void exddx(dplan *d);
void exint(dplan *d);

/* void plddxm(double *y, double *ty, double *dy, int n, fftw_plan *p1, fftw_plan *p2); */

/* void exddxm(double * restrict ty, double * restrict dy, double * restrict b, const int n, const fftw_plan p1, const fftw_plan p2); */



/* void plddx(double *y, double *ty, double *dy, fftw_plan *p1, fftw_plan *p2); */

/* void exddx(double * restrict ty, double * restrict dy, double b, const fftw_plan p1, const fftw_plan p2); */

/* void plint(double *y, double *ty, double *iy, fftw_plan *p1, fftw_plan *p2); */

/* void exint(double * restrict ty, double *restrict y, double * restrict iy, double b, const fftw_plan p1, const fftw_plan p2); */
