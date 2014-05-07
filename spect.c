/*
 * Spectral routines: containing all things spectral! (including the ghosts)
 */
#include <math.h>
#include <fftw3.h>
#include "spect.h"

// Long double of Pi. We can beat MMA with this.
#define M_PIl 3.1415926535897932384626433832795029L

// Matrices to be constructed
static double REBASEM[N+1][N+1]; // Rebasing
static double DDXM[N+1][N+1]; // Derivatives
static double INTM[N+1][N+1]; // Integration
static double DDXME[N+1][N+1]; // Even mode derivatives
static double INTME[N+1][N+1]; // Even mode integration
static double FILTERM[N+1][N+1]; // Matrix for filtering

// BLAS Routines
// Matrix . vector
extern void dgemv_(const char *, const int *, const int *, const double *, const double *, const int *, const double *, const int *, const double *, double *, const int *);
// Copy
extern void dcopy_(const int *, const double *, const int *, double *, const int *);
// Dot product
extern double ddot_(const int *, const double *, const int *, const double *, const int *);
// aX + Y
extern void daxpy_(const int *, const double *, const double *, const int *, double *, const int *);

// Data needed for taking derivatives
typedef struct dplan{
  long double * yin; //input
  long double * yout; //output
  long double * ty; //temp
  fftwl_plan p[2]; //plans for transforming
} dplan;

// Data needed for rebasing
typedef struct flyplan{
  long double * y;
  fftwl_plan p;
  int n;
} flyplan;

// Initialises grid points and their weights
static void mkwi(long double *x){
  int i=N+1; while(i-->0){
    //  for(i=0;i<N;i++){
    x[i]=-cosl(M_PIl*i/N); //x
    x[i+(N+1)]=1/(-2*N*sinl(M_PIl*i/N)); //w
    x[i+2*(N+1)]=sinl(M_PIl*i/N)/(-2*N); //iw
  }
}

// Initialises grid points and their weights for even modes
static void mkwie(long double *x){
  int i=N+1; while(i-->0){
    x[i+(N+1)]=1/(-1*N*sinl(.5*M_PIl*(N-i)/N)); //w
    x[i+2*(N+1)]=sinl(.5*M_PIl*(N-i)/N)/(-4*N); //iw    
  }
}

static void plddx(dplan *d){
  // plddx plans a differentiation operation on the data stored at d->yin to output to d->yout.

  const fftw_r2r_kind t[]={FFTW_REDFT00,FFTW_RODFT00};
  d->p[0]=fftwl_plan_r2r_1d(N+1,d->yin,d->ty,t[0],FFTW_ESTIMATE);
  d->p[1]=fftwl_plan_r2r_1d(N-1,d->ty+1,d->yout+1,t[1],FFTW_ESTIMATE);
}

static void plint(dplan *d){
  // plint plans an integration operation on d->yin to output to d->yout.
  long double *TY=d->ty;
  const fftw_r2r_kind t[]={FFTW_RODFT00,FFTW_REDFT00};
  d->p[0]=fftwl_plan_r2r_1d(N-1,d->yin+1,TY+1,t[0],FFTW_ESTIMATE);
  d->p[1]=fftwl_plan_r2r_1d(N+1,TY,d->yout,t[1],FFTW_ESTIMATE);
}

// Rebasing plan
static void plfly(flyplan *f){
  const fftw_r2r_kind t[]={FFTW_REDFT00};
  const int n[]={N+1};
  const int e[]={N+2};
  f->p=fftwl_plan_many_r2r(1,n,f->n,f->y,NULL,1,N+1,f->y,NULL,1,N+1,t,FFTW_ESTIMATE);
}

static void exddx(dplan *d, long double *x){
	// executes a planed differentiation using:
	// y = sum(a_n T_n(x)) = sum(a_n cos(n \theta)
	//   => y' = sum(a_n n sin(n \theta) / sin(\theta))

	long double *WEIGHTS = x+N+1;
	long double *TY=x+3*(N+1);

	long double a=0,b=0;
	int i;

	fftwl_execute(d->p[0]);

	i=N;
	while(i-->1){
		TY[i]*=i;
		a+=i*TY[i];
		b+=i*TY[i]*(2*(i&1)-1);
	}
	a/=-N;
	b/=-N;

	a+=-N*.5*TY[N];
	b+=-N*.5*TY[N]*(2*(N&1)-1);

	d->yout[0]=a;
	d->yout[N]=b;

	fftwl_execute(d->p[1]);

	i=N; while(i-->1){
		d->yout[i]*=WEIGHTS[i];
	}
}


static void exintl(dplan *d, long double a, long double *x){
	// executes a planed integration using the reverse of the technique in exddx. Currently destroys data in yin. Perhaps this can be avoided with some fourier identity magic and a multiplication at the end instead of the begining.

	long double *IWEIGHTS = x+2*(N+1);
	long double *TY = x+3*(N+1);

	int i;
	long double b=0;

#pragma GCC ivdep
	i=N; while(i-->1){
		//for(i=0;i<N;i++){
		d->yin[i]*=IWEIGHTS[i]; // note: input is destroyed. don't think we care.
	}

	fftwl_execute(d->p[0]);

#pragma GCC ivdep
	i=N; while(i-->2){
		//  for(i=2;i<N+1;i++){
		b+=(i)*TY[i]*(1-(N+i&1));
		TY[i]/=i;
		a+=-2*TY[i];
	}

	b+=TY[1]*(N&1);

	TY[N]=(-2)*(b+((2*(1&N)-1)*d->yin[N]+d->yin[0])/4)/(N*N);
	TY[0]=(a-(TY[N]+2*TY[1]));

	fftwl_execute(d->p[1]);
}

// Rebases a grid to a new grid
// Left and right are the new endpoints; old endpoints are -1 and 1. y is both input and output
static void exfly(flyplan *f ,long double left, long double right, long double *y){
	long double *X=y;
	long double x[N+1];
	long double *a=f->y;
	long double b[2][N+1];
	long double a0=0;
	int i,j,k;

	j=N+1; while(j-->0){
		x[j]=-(.5*(right-left)*X[j]+.5*(right+left));
	}

	fftwl_execute(f->p);

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

// Initializes matrix to take derivative
static void plddxm(long double *x){
	// Fills derivative matrix by taking derivatives of individual points
	int i,j;
	long double ddxm[N+1];
	dplan ddx;
	i=N+1;while(i-->0){
		ddx.yin=ddxm;
		ddx.yout=ddxm;
		ddx.ty=x+3*(N+1);
		plddx(&ddx);
		j=N+1;while(j-->0){
			ddxm[j]=i==j?1:0;
		}
		exddx(&ddx,x);
		// Storing the data
		j=N+1;while(j-->0){
			DDXM[i][j]=(double) ddxm[j];
		}
	}
}

// Initializes matrix for integration
static void plintm(long double *x){
	// Fills integration matrix by taking integrals of individual points
	int i,j;
	long double xddm[N+1];
	dplan xdd;
	i=N+1;while(i-->0){
		xdd.yin=xddm;
		xdd.yout=xddm;
		xdd.ty=x+3*(N+1);
		plint(&xdd);
		j=N+1;while(j-->0){
			xddm[j]=i==j?1:0;
		}
		exintl(&xdd,0,x);
		j=N+1;while(j-->0){
			INTM[i][j]=(double)xddm[j];
		}
	}
}

// Initializes matrix for rebasing
// Right end point is held fixed, grid is shrunk by a factor of "a".
static void plrebase(double a, long double *x){
	// Fills rebasing matrix
	int i,j;
	flyplan fpl;
	long double tmpm[N+1];
	fpl.y=tmpm;
	fpl.n=1;
	plfly(&fpl);
	i=N+1;while(i-->0){
		j=N+1;while(j-->0){
			tmpm[j]=i==j?1:0;
		}
		exfly(&fpl,1-2*a,1,x);
		j=N+1;while(j-->0){
			REBASEM[i][j]=(double)tmpm[j];
		}
	}
}

// Initializes matrix for filtering
static void plfilter(){
	int i,j;
	long double t[N+1];
	fftwl_plan p;
	// Plan to go to Fourier space
	p=fftwl_plan_r2r_1d(N+1,t,t,FFTW_REDFT00,FFTW_ESTIMATE);
	// Loop over every point
	i=N+1;while(i-->0){
		// On the ith point, set the jth entry of the temporary vector to zero unless i = j
		j=N+1;while(j-->0){
			t[j]=i==j?1:0;
		}
		// Transform to Fourier space
		fftwl_execute(p);
		// Filtering
		j=N+1; while(j-->0){
			// t[j]*=expl(-36*powl(j*1.0/(N+1),32));
			t[j]*=expl(-48*powl(j*1.0/(N+1),24));
		}
		// Normalize to get back to real space
		j=N+1; while(j-->0){
			t[j]/=2*N;
		}
		// Go back to real space
		fftwl_execute(p);
		// Store the results
		j=N+1; while(j-->0){
			FILTERM[i][j]=(double)t[j];
		}
	}
}

// Derivatives on even modes, setup
void plddxme(long double *x){
	int i,j;
	long double ddxm[N+1];
	dplan ddx;
	i=N+1;while(i-->0){
		ddx.yin=ddxm;
		ddx.yout=ddxm;
		ddx.ty=x+3*(N+1);
		plddx(&ddx);
		j=N+1;while(j-->0){
			ddxm[j]=i==j?1:0;
		}
		exddx(&ddx,x);
		DDXME[i][N]=(double) 4*ddxm[N];
		j=N;while(j-->1){
			DDXME[i][j]=(double) ddxm[j];
		}
		DDXME[i][0]=0;
	}
}

// Integration on even modes, setup
static void plintme(long double *x){
	// Fills integration matrix
	int i,j;
	long double xddm[N+1];
	dplan xdd;
	i=N+1;while(i-->0){
		xdd.yin=xddm;
		xdd.yout=xddm;
		xdd.ty=x+3*(N+1);
		plint(&xdd);
		j=N+1;while(j-->0){
			xddm[j]=i==j?1:0;
		}
		// xddm[0]=0;
		xddm[N]*=1;
		exintl(&xdd,0,x);
		j=N+1;while(j-->0){
			INTME[i][j]=(double)xddm[j];
		}
	}
}

/* Actual Functions worth calling */
void spectSetup(double a){
	// Sets up doing spectral method things using matrix stuff. a is the ratio of the rebasing.
	long double x[(N+1)*4];
	mkwi(x); // Grid points and weights
	plddxm(x); // Derivs
	plintm(x); // Ints
	plrebase(a,x); // Rebase
	plfilter(); // Filter
	mkwie(x); // Even grid
	plddxme(x); // Even derivs
	plintme(x); // Even ints

	// Kill plans now.
	// TO DO
}

// Matrix-vector multiplies (ooh, fancy): Integration
void intm(const double *y, double *dy){
	//integrates y from left boundary, outputs to dy.
	int n[]={N+1,1};
	double a[]={1.0,0.0};
	dgemv_("n",n,n,a,&INTM[0][0],n,y,n+1,a+1,dy,n+1);
}

// Matrix-vector multiplies (ooh, fancy): Differentiation
void ddxm(const double *y, double *dy){
	//takes derivative of y, outputs to dy
	int n[]={N+1,1};
	double a[]={1.0,0.0};
	dgemv_("n",n,n,a,&DDXM[0][0],n,y,n+1,a+1,dy,n+1);
}

// Take the derivative at x=-1.
double ddxm0(const double *y){
	int n[]={N+1,1};
	return ddot_(n,&DDXM[0][0],n+1,y,n+1);
}

// Matrix-vector multiplies (ooh, fancy): Rebasing
void rebasem(double *y){
	//takes y and rebases it on a smaller domain.
	double x[N+1];
	int n[]={N+1,1};
	double a[]={1.0,0.0};
	dcopy_(n,y,n+1,x,n+1);
	dgemv_("n",n,n,a,&REBASEM[0][0],n,x,n+1,a+1,y,n+1);
}

// Matrix-vector multiplies (ooh, fancy): Filtering
void filterm(double *y){
	double x[N+1];
	int n[]={N+1,1};
	double a[]={1.0,0.0};
	dcopy_(n,y,n+1,x,n+1);
	dgemv_("n",n,n,a,&FILTERM[0][0],n,x,n+1,a+1,y,n+1);
}

// Matrix-vector multiplies (ooh, fancy): Integration (even)
void intme(const double *y, double *dy){
	//integrates y using even modes.
	int n[]={N+1,1};
	double a[]={1.0,0.0};
	dgemv_("n",n,n,a,&INTME[0][0],n,y,n+1,a+1,dy,n+1);
}

// Matrix-vector multiplies (ooh, fancy): Differentiation (even)
void ddxme(const double *y, double *dy){
	//takes derivative of y using even modes.
	int n[]={N+1,1};
	double a[]={1.0,0.0};
	dgemv_("n",n,n,a,&DDXME[0][0],n,y,n+1,a+1,dy,n+1);
}

// Interpolate data from Chebyshev polynomials
// y is input data
// x is where you want the value
double chebInterp(double *y, double x){
	// Compute coefficients in phase space
	double a[N+1]; //coefficients
	fftw_plan p = fftw_plan_r2r_1d(N+1,y,a,FFTW_REDFT00,FFTW_ESTIMATE);
	fftw_execute(p);

	// More variables
	double b[2];
	long double a0=0;
	int i;

	// Evaluate the Chebyshev polynomials at x in a clever way
	b[1]=a[N-1]+1*x*a[N];
	b[0]=a[N-2]+2*x*b[1]-.5*a[N];

	// Loop
	i=N-3; while(i-->1){
		b[i&1] = a[i-1] + 2*x*b[(i+1)&1] - b[i&1];
	}

	// Destroy the plan
	fftw_destroy_plan(p);

	// Return the result
	return (a[0]/2+x*b[1]-b[0])/N;

}
