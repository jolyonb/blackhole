#include <math.h>
#include "spect.h"

static double WEIGHTS[N];
static double IWEIGHTS[N];
static double TY[N+1];

void mkwi(){
  int i=N;
  while(i-->0){
    WEIGHTS[i]=1/(-2*N*sin(M_PI*(i+.5)/N));
    IWEIGHTS[i]=sin(M_PI*(i+.5)/N)/(-2*N);
  }
}

void plddx(dplan *d){
  // plddx plans a differentiation operation on the data stored at d->y to output to d->dy

  const fftw_r2r_kind t[]={FFTW_REDFT10,FFTW_RODFT01};
  d->p[0]=fftw_plan_r2r_1d(N,d->yin,TY,t[0],FFTW_EXHAUSTIVE);
  d->p[1]=fftw_plan_r2r_1d(N,TY+1,d->yout,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plint(dplan *d){
  // plint plans an integration operation on d->y to output to d->dy. Sorry oubout the name, I wrote the differentiater first.
  
  const fftw_r2r_kind t[]={FFTW_RODFT10,FFTW_REDFT01};
  d->p[0]=fftw_plan_r2r_1d(N,d->yin,TY+1,t[0],FFTW_EXHAUSTIVE);
  d->p[1]=fftw_plan_r2r_1d(N,TY,d->yout,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void exddx(dplan *d){
  // executes a planed differentiation using:
  // y = sum(a_n T_n(x)) = sum(a_n cos(n \theta)
  //   => y' = sum(a_n n sin(n \theta) / sin(\theta))


  double b=d->b;
  fftw_execute(d->p[0]);

  int i;
  i=N;
  b*=N;
  while(i-->1){
    b+=TY[i]*(2*(i&1)-1);
    TY[i]*=i;
  }
  TY[N]=(b-.5*TY[0]); //setting the boundary condition
  
  fftw_execute(d->p[1]);

  i=N;

  #pragma GCC ivdep
  while(i-->0){
     d->yout[i]*=WEIGHTS[i];
  }  
}

void exddxl(dplan *d){
  //puts the boundary condition on the left.
  
  double b=d->b;
  fftw_execute(d->p[0]);

  unsigned int i;
  i=N;
  b*=N;
  while(i-->1){
    b-=TY[i];
    TY[i]*=i;
  }
  TY[N]=(b-.5*TY[0]); //setting the boundary condition
  
  fftw_execute(d->p[1]);

  i=N;

  #pragma GCC ivdep
  while(i-->0){
     d->yout[i]*=WEIGHTS[i];
  }  
}

void exint(dplan *d){
  // executes a planed integration using the reverse of the technique in exddx.

  unsigned int i;
  double b=d->b;
  i=N;

  //icc is much faster in this function. I think because it handles the following loop better.
  //I changed my mind. I really don't know why it's faster. it [GCC] seems to vectorize the loops just fine.

  #pragma GCC ivdep
  while(i-->0){
    d->yin[i]*=IWEIGHTS[i]; // note: input is destroyed. don't think we care.
  }
      
  fftw_execute(d->p[0]);

  i=N+1;
  while(i-->2){
    TY[i]/=i;
    b+=2*TY[i]*(2*(i&1)-1);
  }
  TY[0]=b+2*TY[1]; //setting the boundary condition
  
  fftw_execute(d->p[1]);
}
