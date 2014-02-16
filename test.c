#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include "spect.h"
//#include "misner-sharp.c"

int main(){
  mkwi();
  double x[N];
  double *y=fftw_alloc_real(N);
  double *dy=fftw_alloc_real(N);
  dplan meee;
  meee.yin=y;
  meee.yout=dy;
  meee.b=0;
  int i=N;
  int j;

  plddx(&meee);
  //plddx(&meee);

  while(i-->0){
    x[i]=-cos(M_PI*(i+.5)/N);
    // y[i]=0;
    //y[i]=x[i]+1;
    //y[i]=-1+2*x[i]*x[i];
    y[i]=sin(x[i])*(1-x[i]);
    //y[i]*=y[i];
  }

  i=1;while(i-->0){
    //exddx(&meee);
    exddx(&meee);
    
    //j=N; while(j-->0) y[j]=sin(x[j]);
  }
  
  double m,a,fma;

  //fftw_flops(meee.p[0],&m,&a,&fma);
  //  printf("%f\t%f\t%f\n",m,a,fma);
  // fftw_print_plan(meee.p[0]);
  dplan das[2];
  printf("%d\n",sizeof(das));
  printf("%p\t%p\n",das,das+1);

  for(i=0;i<N;i++){
    //printf("%f\t%f\t%f\n",x[i],y[i],dy[i]);
  }
  return 0;
}
