#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include "spect.h"
#include "misner-sharp.c"

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
  state meeee;
  flyplan fpl;
  fpl.y=y;
  fpl.n=1;
  
  msSetup(&meeee);

  plddx(&meee);
  //plddx(&meee);
  plfly(&fpl);

  while(i-->0){
    x[i]=-cos(M_PI*(i+.5)/N);
    // y[i]=0;
    //y[i]=x[i];
    //y[i]=x[i]*x[i];
    dy[i]=sin((1+x[i])*.8/2+.2)+cos((1+x[i])*.8/2+.2);
    //y[i]=-1+2*x[i]*x[i];
    //y[i]=sin(x[i])*(1-x[i]);
    //y[i]*=y[i];
  }

  i=10;while(i-->0){
    j=N; while(j-->0) y[j]=sin(x[j])+cos(x[j]);
     exfly(&fpl,0.2,1.0);
    //exddx(&meee);
    
    
  }
  
  double m,a,fma;

  //fftw_flops(meee.p[0],&m,&a,&fma);
  //  printf("%f\t%f\t%f\n",m,a,fma);
  // fftw_print_plan(meee.p[0]);
  dplan das[2];
  //  printf("%d\n",sizeof(das));
  //  printf("%p\t%p\n",das,das+1);

  for(i=0;i<N;i++){
    //printf("%f\t%f\t%f\n",meeee.umr.u[i],meeee.umr.m[i],meeee.umr.r[i]);
    printf("%f\t%f\t%f\n",x[i],y[i],dy[i]);
  }
  
  return 0;
}
