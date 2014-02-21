#include <math.h>
#include <cblas.h>
#include "spect.h"


static double X[N+1];
static double WEIGHTS[N+1];
static double IWEIGHTS[N+1];
static double TY[N+1];
static double REBASEM[N+1][N+1];
static double DDXM[N+1][N+1];
static double INTM[N+1][N+1];

void spectSetup(double a){
  mkwi();
  plddxm();
  plintm();
  plrebase(a);
}

void mkwi(){
  int i=N+1; while(i-->0){
    //  for(i=0;i<N;i++){
    X[i]=-cos(M_PI*i/N);
    WEIGHTS[i]=1/(-2*N*sin(M_PI*i/N));
    IWEIGHTS[i]=sin(M_PI*i/N)/(-2*N);
  }
}

void plddx(dplan *d){
  // plddx plans a differentiation operation on the data stored at d->yin to output to d->yout.

  const fftw_r2r_kind t[]={FFTW_REDFT00,FFTW_RODFT00};
  d->p[0]=fftw_plan_r2r_1d(N+1,d->yin,TY,t[0],FFTW_EXHAUSTIVE);
  d->p[1]=fftw_plan_r2r_1d(N-1,TY+1,d->yout+1,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plint(dplan *d){
  // plint plans an integration operation on d->yin to output to d->yout.
  
  const fftw_r2r_kind t[]={FFTW_RODFT00,FFTW_REDFT00};
  d->p[0]=fftw_plan_r2r_1d(N-1,d->yin+1,TY+1,t[0],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
  d->p[1]=fftw_plan_r2r_1d(N+1,TY,d->yout,t[1],FFTW_EXHAUSTIVE | FFTW_DESTROY_INPUT);
}

void plfly(flyplan *f){
  const fftw_r2r_kind t[]={FFTW_REDFT00};
  const int n[]={N+1};
  const int e[]={N+2};
  f->p=fftw_plan_many_r2r(1,n,f->n,f->y,NULL,1,N+1,f->y,NULL,1,N+1,t,FFTW_EXHAUSTIVE);
}

void plddxm(){
  int i,j;
  dplan ddx;
  //for(i=0;i<N;i++){
  i=N+1;while(i-->0){
    ddx.yin=DDXM[i];
    ddx.yout=DDXM[i];
    plddx(&ddx);
    j=N+1;while(j-->0){
      DDXM[i][j]=i==j?1:0;
    }
    exddx(&ddx);
  }
}

void plintm(){
  int i,j;
  dplan xdd;
  i=N+1;while(i-->0){
    xdd.yin=INTM[i];
    xdd.yout=INTM[i];
    plint(&xdd);
    j=N+1;while(j-->0){
      INTM[i][j]=i==j?1:0;
    }
    exintl(&xdd,0);
  }
}

void plrebase(double a){
  int i,j;
  flyplan fpl;
  fpl.y=&REBASEM[0][0];
  fpl.n=N+1;
  plfly(&fpl);
  i=N+1;while(i-->0){
    j=N+1;while(j-->0){
      REBASEM[i][j]=i==j?1:0;
    }
  }
  exfly(&fpl,1-2*a,1);
}


void exddx(dplan *d){
  // executes a planed differentiation using:
  // y = sum(a_n T_n(x)) = sum(a_n cos(n \theta)
  //   => y' = sum(a_n n sin(n \theta) / sin(\theta))
  
  double a,b=0;
  int i;

  fftw_execute(d->p[0]);
  
  #pragma GCC ivdep
  i=N; while(i-->1){
  //for(i=1;i<N;i++){
    TY[i]*=i; 
    a+=i*TY[i];
    b+=i*TY[i]*(2*(i&1)-1);
  }
  a/=-N;
  b/=-N;
  
  a+=-N*TY[N];
  b+=-N*TY[N]*(2*(N&1)-1); 
  d->yout[0]=a;
  d->yout[N]=b;
  
  fftw_execute(d->p[1]);

  #pragma GCC ivdep
  i=N; while(i-->1){
    //for(i=0;i<N;i++){
    d->yout[i]*=WEIGHTS[i];
  }
}

void exintr(dplan *d, double a){
  // executes a planed integration using the reverse of the technique in exddx. Currently destroys data in yin. Perhaps this can be avoided with some fourier identity magic and a multiplication at the end instead of the begining.

  int i;
  double b=0;

  #pragma GCC ivdep
  i=N; while(i-->1){
  //for(i=0;i<N;i++){
     d->yin[i]*=IWEIGHTS[i]; // note: input is destroyed. don't think we care.
  }

  fftw_execute(d->p[0]);

  /* i=N/2;while(i-->1){ */
  /*   b+=(2*i)*TY[2*i]; */
  /* } */

  #pragma GCC ivdep
  i=N; while(i-->2){
    //  for(i=2;i<N+1;i++){
    b+=(i)*TY[i]*(1-(i&1));
    TY[i]/=i;
    a+=2*TY[i]*(2*(i&1)-1);
  }

  TY[N]=-(b-(d->yin[N]-d->yin[0])/4)/(N*N); //This might be assuming N is even. It probably should be anyway.
  TY[0]=(a-(TY[N]-2*TY[1]));

  fftw_execute(d->p[1]);

  /* a-=d->yout[N]; */
  /* i=N+1;while(i-->0){ */
  /*   d->yout[i]+=a; */
  /* } */
}

  void exintl(dplan *d, double a){
  // executes a planed integration using the reverse of the technique in exddx. Currently destroys data in yin. Perhaps this can be avoided with some fourier identity magic and a multiplication at the end instead of the begining.

  int i;
  double b=0;

  #pragma GCC ivdep
  i=N; while(i-->1){
  //for(i=0;i<N;i++){
    d->yin[i]*=IWEIGHTS[i]; // note: input is destroyed. don't think we care.
  }
      
  fftw_execute(d->p[0]);

  #pragma GCC ivdep
  i=N; while(i-->2){
  //  for(i=2;i<N+1;i++){
    b+=(i)*TY[i]*(1-(N+i&1));
    TY[i]/=i;
    a+=-2*TY[i];
  }

  b+=TY[1]*(N&1);


  printf("%f\n",b);

  //  TY[N]=-(b-(d->yin[N]-d->yin[0])/4)/(N*N); //This might be assuming N is even. It probably should be anyway.
  TY[N]=(-2)*(b+((2*(1&N)-1)*d->yin[N]+d->yin[0])/4)/(N*N);
  TY[0]=(a-(TY[N]+2*TY[1]));

  fftw_execute(d->p[1]);
}

void exfly(flyplan *f ,double left, double right){
  double x[N+1];
  double *a=f->y;
  double b[2][N+1]; 
  double a0;
  int i,j,k;

  j=N+1; while(j-->0){
    x[j]=-(.5*(right-left)*X[j]+.5*(right+left));
  }
  
  fftw_execute(f->p);

  k=f->n; while(k-->0){
    j=N+1; while(j-->0){
      // b[1][j]=.5*a[N-1]; //because extremal grid weirdness
      b[1][j]=a[N-1]+1*x[j]*a[N];
      b[0][j]=a[N-2]+2*x[j]*b[1][j]-.5*a[N];
    }

    //i=(N-4)/2; while(i-->0){
    i=N-2; while(i-->1){
      j=N+1; while(j-->0){
	b[i&1][j]=a[i]+2*x[j]*b[(i+1)&1][j]-b[i&1][j];

	//b[0][j]=a[i*2+2]+2*x[j]*b[1][j]-b[0][j];
	//b[1][j]=a[i*2+1]+2*x[j]*b[0][j]-b[1][j];
      }
    }

    a0=a[0];

    j=N+1; while(j-->0){
      a[j]=(a0/2+x[j]*b[1][j]-b[0][j])/N;
    }
    a+=N+1;
  }
}

void intm(double *y, double *dy){
  cblas_dgemv(CblasRowMajor,CblasTrans,N+1,N+1,1,INTM[0],N+1,y,1,0,dy,1);
}

void ddx(double *y, double *dy){
  cblas_dgemv(CblasRowMajor,CblasTrans,N+1,N+1,1,DDXM[0],N+1,y,1,0,dy,1);
}

void exrebase(double *y){
  double x[N+1];
  int i=N+1; while(i-->0){
    x[i]=y[i];
  }
  cblas_dgemv(CblasRowMajor,CblasTrans,N+1,N+1,1,&REBASEM[0][0],N+1,x,1,0,y,1);
}
