#include <math.h>
#include "spect.h"

static double X[N];
static double WEIGHTS[N];
static double IWEIGHTS[N];
static double TY[N+1];

void mkwi(){
  int i=N; while(i-->0){
    //  for(i=0;i<N;i++){
    X[i]=-cos(M_PI*(i+.5)/N);
    WEIGHTS[i]=1/(-2*N*sin(M_PI*(i+.5)/N));
    IWEIGHTS[i]=sin(M_PI*(i+.5)/N)/(-2*N);
  }
}

void plddx(dplan *d){
  // plddx plans a differentiation operation on the data stored at d->yin to output to d->yout.

  const fftw_r2r_kind t[]={FFTW_REDFT10,FFTW_RODFT01};
  d->p[0]=fftw_plan_r2r_1d(N,d->yin,TY,t[0],FFTW_EXHAUSTIVE);
  d->p[1]=fftw_plan_r2r_1d(N,TY+1,d->yout,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plint(dplan *d){
  // plint plans an integration operation on d->yin to output to d->yout.
  
  const fftw_r2r_kind t[]={FFTW_RODFT10,FFTW_REDFT01};
  d->p[0]=fftw_plan_r2r_1d(N,d->yin,TY+1,t[0],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
  d->p[1]=fftw_plan_r2r_1d(N,TY,d->yout,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plfly(flyplan *f){
  const fftw_r2r_kind t[]={FFTW_REDFT10};
  const int n[]={N};
  f->p=fftw_plan_many_r2r(1,n,f->n,f->y,NULL,1,N,f->y,NULL,1,N,t,FFTW_EXHAUSTIVE);
  //  f->p=fftw_plan_r2r_1d(N,f->y,f->y,t[0],FFTW_EXHAUSTIVE);
}

void exddx(dplan *d){
  // executes a planed differentiation using:
  // y = sum(a_n T_n(x)) = sum(a_n cos(n \theta)
  //   => y' = sum(a_n n sin(n \theta) / sin(\theta))


  double b=d->b*N;
  int i;

  fftw_execute(d->p[0]);
  
  //Testing of these functions has shown reverse looping to be faster. Commented out are the equivalent forward loops.

  #pragma GCC ivdep
  i=N; while(i-->1){
  //for(i=1;i<N;i++){
    b+=TY[i]*(2*(i&1)-1);
    TY[i]*=i;
  }
  TY[N]=(b-.5*TY[0]); //setting the boundary condition
  
  fftw_execute(d->p[1]);

  #pragma GCC ivdep
  i=N; while(i-->0){
  //for(i=0;i<N;i++){
     d->yout[i]*=WEIGHTS[i];
  }  
}

void exddxl(dplan *d){
  //puts the boundary condition on the left.
  
  double b=d->b*N;
  int i;

  fftw_execute(d->p[0]);

  #pragma GCC ivdep
  i=N; while(i-->1){
  //  for(i=1;i<N;i++){
    b-=TY[i];
    TY[i]*=i;
  }
  TY[N]=(b-.5*TY[0]); //setting the boundary condition
  
  fftw_execute(d->p[1]);

  #pragma GCC ivdep
  i=N; while(i-->0){
  //for(i=0;i<N;i++){
     d->yout[i]*=WEIGHTS[i];
  }  
}

void exint(dplan *d){
  // executes a planed integration using the reverse of the technique in exddx. Currently destroys data in yin. Perhaps this can be avoided with some fourier identity magic and a multiplication at the end instead of the begining.

  int i;
  double b=d->b;

  #pragma GCC ivdep
  i=N; while(i-->0){
  //for(i=0;i<N;i++){
    d->yin[i]*=IWEIGHTS[i]; // note: input is destroyed. don't think we care.
  }
      
  fftw_execute(d->p[0]);

  #pragma GCC ivdep
  i=N+1; while(i-->2){
  //  for(i=2;i<N+1;i++){
    TY[i]/=i;
    b+=2*TY[i]*(2*(i&1)-1);
  }
  TY[0]=b+2*TY[1]; //setting the boundary condition
  
  fftw_execute(d->p[1]);
}

void exfly(flyplan *f ,double left, double right){
  double x[N];
  double *a=f->y;
  double b[2][N]; 
  double a0;
  int i,j,k;

  j=N; while(j-->0){
    x[j]=-(.5*(right-left)*X[j]+.5*(right+left));
  }
  
  fftw_execute(f->p);

  k=f->n; while(k-->0){
    j=N; while(j-->0){
      // b[1][j]=a[N-1];
      b[0][j]=a[N-2]+2*x[j]*a[N-1];
      b[1][j]=a[N-3]+2*x[j]*b[0][j]-a[N-1];
    }

    //i=(N-4)/2; while(i-->0){
    i=N-3; while(i-->1){
      j=N; while(j-->0){
	b[i&1][j]=a[i]+2*x[j]*b[(i+1)&1][j]-b[i&1][j];

	//b[0][j]=a[i*2+2]+2*x[j]*b[1][j]-b[0][j];
	//b[1][j]=a[i*2+1]+2*x[j]*b[0][j]-b[1][j];
      }
    }

    a0=a[0];

    j=N; while(j-->0){
      a[j]=(a0/2+x[j]*b[1][j]-b[0][j])/N;
    }
    a+=N;
  }
}
