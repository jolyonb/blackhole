#include <math.h>
#include <fftw3.h>
#include "spect.h"

static double WEIGHTS[N];
static double IWEIGHTS[N];
static double TY[N+1];

void mkwi(){
  int i=N;
  //TY=fftw_alloc_real(N+1);
  while(i-->0){
    WEIGHTS[i]=1/(-2*N*sin(M_PI*(i+.5)/N));
    IWEIGHTS[i]=sin(M_PI*(i+.5)/N)/(-2*N);
  }
}

void plddx(dplan *d){
   const fftw_r2r_kind t[]={FFTW_REDFT10,FFTW_RODFT01};
   //   double *y=d->y;
   d->p[0]=fftw_plan_r2r_1d(N,d->y,TY,t[0],FFTW_EXHAUSTIVE);
   d->p[1]=fftw_plan_r2r_1d(N,TY+1,d->dy,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plint(dplan *d){
  const fftw_r2r_kind t[]={FFTW_RODFT10,FFTW_REDFT01};
  d->p[0]=fftw_plan_r2r_1d(N,d->dy,TY+1,t[0],FFTW_EXHAUSTIVE);
  d->p[1]=fftw_plan_r2r_1d(N,TY,d->dy,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void exddx(dplan *d){
  double b=d->b;
  fftw_execute(d->p[0]);

  unsigned int i;
  i=N;
  b*=N;
  while(i-->1){
    b-=TY[i];
    TY[i]*=i;
  }
  TY[N]=(b-.5*TY[0]);
  
  fftw_execute(d->p[1]);

  i=N;
  while(i-->0){
     d->dy[i]*=WEIGHTS[i];
  }  
}

void exint(dplan *d){
  int i;
  double b=d->b;
  i=N;
  while(i-->0){
     d->dy[i]=d->y[i]*IWEIGHTS[i];
  }
      
  fftw_execute(d->p[0]);

  i=N+1;
  while(i-->2){
    TY[i]/=i;
    b+=2*TY[i]*(2*(i&1)-1);
  }
  TY[0]=b+2*TY[1];
  
  fftw_execute(d->p[1]);
}


/* 
 * Potentially not useful after here. Probably just ignore.
 */

void plddxm(double *y, double *ty, double *dy, int n, fftw_plan *p1, fftw_plan *p2){
  const int d[]={N};
  const fftw_r2r_kind t[]={FFTW_REDFT10,FFTW_RODFT01};
  *p1=fftw_plan_many_r2r(1,d,n,y,NULL,1,N,ty,NULL,1,N,t,FFTW_EXHAUSTIVE);
  *p2=fftw_plan_many_r2r(1,d,n,ty+1,NULL,1,N,dy,NULL,1,N,t+1,FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plddxd(double *y, double *ty, double *dy, fftw_plan *p1, fftw_plan *p2){
//void(dplan d){
  const fftw_r2r_kind t[]={FFTW_REDFT10,FFTW_RODFT01};
  //*p1=fftw_plan_r2r_1d(N,y,ty,t[0],FFTW_EXHAUSTIVE);
  //*p2=fftw_plan_r2r_1d(N,ty+1,dy,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
  *p1=fftw_plan_r2r_1d(N,y,TY,t[0],FFTW_EXHAUSTIVE);
  *p2=fftw_plan_r2r_1d(N,TY+1,dy,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plintd(double *y,double *ty, double *iy, fftw_plan *p1, fftw_plan *p2){
  const fftw_r2r_kind t[]={FFTW_RODFT10,FFTW_REDFT01};
  *p1=fftw_plan_r2r_1d(N,iy,ty+1,t[0],FFTW_EXHAUSTIVE);
  *p2=fftw_plan_r2r_1d(N,ty,iy,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

//Potentially not useful.
void exddxm(double *restrict ty, double *restrict dy, double *restrict b, const int n, const fftw_plan p1, const fftw_plan p2){

  fftw_execute(p1);
 
  //printf("%f\n",b[0]);

  unsigned int i;
  unsigned int j=n;
  while(j-->0){
    i=N;
    b[j]*=N;
    while(i-->1){
      b[j]-=ty[i+(N)*j];
      ty[i+(N)*j]*=i;
    }
    ty[N+(N)*j]=N*(b[j]-.5*ty[(N)*j]);
  }
  
  //printf("%f\n",ty[N]);

  /* int i=n; while(i-->0){ */
  /*   b[i]*=N; */
  /* } */

  /* i=(N-1)*n; */
  /* while (i-->0){ */
  /*   b[i/(N-1)]-=ty[i+2*i/(N-1)+1]; */
  /*   ty[i+2*i/(N-1)+1]*=(i%(N-1))+1; */
  /* } */
  
  /* i=n; while(i-->0){ */
  /*   ty[i*(N+1)+N]=N*(b[i]-.5*ty[(N+1)*i]); */
  /* } */

  fftw_execute(p2);

  i=N*n;
  while(i-->0){
     dy[i]*=WEIGHTS[i%N];
  }
}

void exddxd(double *restrict ty, double *restrict dy, double b, const fftw_plan p1, const fftw_plan p2){

  fftw_execute(p1);

  unsigned int i;
  i=N;
  b*=N;
  while(i-->1){
    b-=TY[i];
    TY[i]*=i;
  }
  ty[N]=N*(b-.5*TY[0]);
  

  fftw_execute(p2);

  i=N;
  while(i-->0){
     dy[i]*=WEIGHTS[i];
  }
}

void exintd(double * restrict ty, double *restrict y, double *restrict iy, double b, const fftw_plan p1, const fftw_plan p2){
  int i;
  
  i=N;
  while(i-->0){
     iy[i]=y[i]*IWEIGHTS[i];
  }
      
  fftw_execute(p1);

  i=N+1;
  while(i-->2){
    ty[i]/=i;
    b+=2*ty[i]*(2*(i&1)-1);
  }
  ty[0]=b+2*ty[1];
  
  fftw_execute(p2);
}
