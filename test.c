#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include "spect.h"

int main(){
  mkwi();
  double x[N];
  double *y=fftw_alloc_real(N);
  double *dy=fftw_alloc_real(N);
  dplan meee;
  meee.y=y;
  meee.dy=dy;
  meee.b=1;
  int i=N;

  plint(&meee);
  //plddx(&meee);

  while(i-->0){
    x[i]=-cos(M_PI*(i+.5)/N);
    // y[i]=0;
    //y[i]=x[i];
    //y[i]=-1+2*x[i]*x[i];
    y[i]=sin(x[i]);
    //y[i]*=y[i];
  }

  i=1;while(i-->0){
    //exddx(&meee);
    exint(&meee);
  }

  for(i=0;i<N;i++){
    printf("%f\t%f\t%f\n",x[i],y[i],dy[i]);
  }
  return 0;
}
