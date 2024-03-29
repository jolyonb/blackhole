// Stuff that should be in the standard but isn't
#include <math.h>
// ODE Integration methods
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
// Spectral methods
#include "spect.h"
#include "misner-sharp.h"

// Value of R at the boundary at the initial time
// Ie, size of the domain
double AFRW;

//regridding ratio
double RATIO;

//Value of A[0]. becomes != 0 after regridding
double A0;

// GSL Stuff
int intfunction(double, const double*, double*, void*);
const gsl_odeiv2_system sys = {&intfunction, NULL, 3*(N+1)+1, NULL};
gsl_odeiv2_step * step;
gsl_odeiv2_control * con;
gsl_odeiv2_evolve * eve;


/* */
/* Equations of motion. */
/* */
inline static double dudt(const dynvar * restrict umr, const resvar * restrict s, int i){
	return -1 * s->phi[i] * \
			( ( s->gamma2[i] * s->drho[i] ) / ( 4 * s->rho[i] * s->dr[i] * umr->r[i]) \
					+ umr->m[i] / umr->r[i] + 4 * M_PI_3 * s->rho[i] + umr->u[i] * umr->u[i] );
}

inline static double dmdt(const dynvar * restrict umr, const resvar * restrict s, int i){
	return -2 * s->phi[i] * umr-> u[i] * ( 2 * M_PI_3 * umr->r[i] * s->rho[i] + umr->m[i] );
}

inline static double drdt(const dynvar * restrict umr, const resvar * restrict s, int i){
	return s->phi[i] * umr->u[i] * umr->r[i];
}

inline static double rho(const dynvar * restrict umr, const resvar * restrict s, int i){
	// Reads m' from rho's spot
	return .25 * M_1_PI * ( s->rho[i] / s->dr[i] + 2 * umr->m[i] / umr->r[i]);
}

inline static double gamma2(const dynvar * restrict umr, const resvar * restrict s, int i){
	//returns \Gamma^2.
	return 8 * M_PI_3 + umr->r[i] * ( umr->u[i] * umr->u[i] * umr->r[i] - 2 * umr->m[i]);
}

/*****/


//calculates u at the origin
inline static double u0(const dynvar * umr){
	double temp[N+1];
	int i;

	//Build U.
	for(i=0;i<N+1;i++){
		temp[i] = umr->u[i] * umr->r[i];
	}

	//u'(0) = U'(0)/R'(0);
	return ddxm0(temp)/ddxm0(umr->r);
}

// Populates the "rest" of the variables
// origin = 1: do the origin specialness because we don't like div by 0
// origin = 0: the left boundary is not R = 0.
static void update(double t, const dynvar * restrict umr, resvar * restrict s){

	// If nothing has changed since we last did our update, then get out
	if (t == s->lastupdated)
		return;

	double irhoFRW;
	int i;
	int origin = A0==0?1:0;


	// Populate gamma2
	s->gamma2[0]=8*M_PI_3;
	i=N+1; while(i-->origin){
		s->gamma2[i]=gamma2(umr,s,i);
	}
	s->gamma2[N]=8*M_PI_3;

	// Take r and m derivatives. Note that m' is stored in rho temporarily
	ddxm(umr->r,s->dr);
	ddxm(umr->m,s->rho);


	// Fix the origin for rho
	if (origin) s->rho[0]=s->rho[0]/(4*M_PI_3*s->dr[0]);
	// Fill rho
	i=N+1; while(i-->origin){
		s->rho[i]=rho(umr,s,i);
	}

	
	// Inverse of FRW rho
	irhoFRW = t * t * M_PI_3 * 32;
	// Pinning of rho at FRW boundary
	s->rho[N]=1/irhoFRW;
	// Some filtering
	filterm(s->rho);
	filterm(s->gamma2);
	// s->rho[N]=1/irhoFRW;
	// s->gamma2[N]=8*M_PI_3;

	// Calculate drho
	ddxm(s->rho,s->drho);

	// Calculate phi
	s->phi[N]=1;
	i=N; while(i-->0){
		s->phi[i]=pow(s->rho[i]*irhoFRW,-.25);
	}

	// Filter phi and set outer boundary to 1 (can be changed from filtering)
	filterm(s->phi);
	s->phi[N]=1;

	// Set the update time
	s->lastupdated = t;
}



/* Integrator */
/* dydt = function(y) */
int intfunction(double t, const double y[], double dydt[], void * params){
	//printf("call at t = %f\n",t);
	int i;
	resvar stuff; // maybe make this params.
	dynvar *umr = (void *) y;
	int origin = A0==0?1:0;
	// Calculate the rest of the values (used in integration)
	update(t,umr,&stuff);


	// Derivatives at the origin
	dydt[0]=0;
	dydt[N+1]=0;
	dydt[2*N+2]=0;

	// Fill integration vector
	i=N+1; while(i-- > origin){
		dydt[i]=dudt(umr,&stuff,i);
		dydt[i+N+1]=dmdt(umr,&stuff,i);
		dydt[i+2*N+2]=drdt(umr,&stuff,i);
	}

	// dA/dt for photon
	double phi = chebInterp(stuff.phi,umr->photon*2-1);
	double gamma = sqrt(chebInterp(stuff.gamma2,umr->photon*2-1));
	double dr = 2.0 * chebInterp(stuff.dr,umr->photon*2-1); // Factor of 2 is because the derivatives are done from -1 to 1
	// instead of 0 to AFRW. The AFRW cancels because A is going from 0 to 1.
	// This works - checked carefully!
	dydt[3*N+3] = phi * gamma / dr;
	

	// Sanity checks
	i=N+1; while(i-->0){
		if(stuff.rho[i]<0){
			//fprintf(stderr, "rho < 0"); // Negative energy density
			return -42;
		}
		// Rest of these are NANs
		if(isnan(umr->u[i])){
			//fprintf(stderr, "u NAN");
			return -42;
		}
		if(isnan(umr->m[i])){
			//fprintf(stderr, "m NAN");
			return -42;
		}
		if(isnan(umr->r[i])){
			//fprintf(stderr, "r nan");
			return -42;
		}
	}

	// Yay us
	return GSL_SUCCESS;
}

// Test for a black hole (-1 for no black hole; grid point for horizon otherwise)
int blackholeQ(dynvar *umr){
	int i;
	int ready=0; // Don't find the cosmological horizon
	for(i=0; i<N+1; i++){
		if (umr->m[i] * umr->r[i] > 4 * M_PI_3) ready=1;
		if (umr->m[i] * umr->r[i] < 4 * M_PI_3 && ready ==1) return i;
	}
	return -1;
}

void regrid(state *s){
	rebasem(s->umr.u);
	rebasem(s->umr.m);
	rebasem(s->umr.r);
	A0 = RATIO * A0 + (1-RATIO) * AFRW;
	s->umr.photon = s->umr.photon / RATIO + (1 - 1/RATIO);
	s->res.lastupdated = -1;
}

static int msEvolveWork(state *s, double t1, double *umrat);

int msEvolve(state* s, double t1, double* umrat) {
    int ret = msEvolveWork(s, t1, umrat);
    // Go and updates values
    update(s->t, &s->umr, &s->res);
    return ret;
}

// Evolve forwards in time to t1. Throws final u,m,R,A,t at photon in umrat
int msEvolveWork(state *s, double t1, double *umrat){

	// Copy of data before step is taken
	state oldstate;

	// Step size
	static double h=1E-3;
	double oldstep;
	int i=0,j;
	while(s->t<t1){ // Before time t1, keep on evolving

		// printf("1something els%e\n", h);


		if (h == 0)
			return 1;

		// Call update on the data
		update(s->t, &s->umr, &s->res);

		// Assert the CFL condition
		oldstep = s->res.phi[0] * (1 - cos(M_PI/N)) / 2;
		if (h > oldstep){
			// fprintf(stderr, "CFL hit\n");
			h = oldstep;
		}

		// Copy data before taking the step
		oldstate.t = s->t;
		oldstep = h;
		for (i = 0; i < N+1; i++) {
			oldstate.umr.m[i] = s->umr.m[i];
			oldstate.umr.r[i] = s->umr.r[i];
			oldstate.umr.u[i] = s->umr.u[i];
			oldstate.umr.photon = s->umr.photon;
			oldstate.res.rho[i] = s->res.rho[i];
		}

		// Take the step
		j=gsl_odeiv2_evolve_apply(eve, con, step, &sys, &s->t, t1, &h, (void *) &s->umr);
		// fprintf(stderr, "photon at %f\n", s->umr.photon);
		// fprintf(stderr, "%e\n", h);
		// Check for error
	// printf("something5 els%e \t %e\n", h, oldstep);

		if (j == -42) {
			s->t = oldstate.t;
			h = oldstep / 10;
			// fprintf(stderr, "rejigging. %e, %e\n", s->t, h);
			for (i = 0; i < N+1; i++) {
				s->umr.m[i] = oldstate.umr.m[i];
				s->umr.r[i] = oldstate.umr.r[i];
				s->umr.u[i] = oldstate.umr.u[i];
				s->umr.photon = oldstate.umr.photon;
			}
			continue;
		}
		if(j!=GSL_SUCCESS) return 1;

	// printf("something2 els%e\n", h);


		// Call update on the data
		update(s->t, &s->umr, &s->res);

		// Check that rho hasn't gone negative
		int redo = 0;
		for (i = 0; i < N+1; i++) {
			if (fabs((s->res.rho[i] - oldstate.res.rho[i])/ oldstate.res.rho[i]) > 0.005 || s->res.rho[i] < 0) {
				redo = 1;
				// fprintf(stderr, "rejigging. %e, %e\n", oldstate.t, oldstep/10);
				break;
			}
		}
		// If redo = 1, then we jumped too far. Reset the state, decrease h, and try again
		if (redo == 1) {
			s->t = oldstate.t;
			h = oldstep / 10;
			for (i = 0; i < N+1; i++) {
				s->umr.m[i] = oldstate.umr.m[i];
				s->umr.r[i] = oldstate.umr.r[i];
				s->umr.u[i] = oldstate.umr.u[i];
				s->umr.photon = oldstate.umr.photon;
			}
			continue;
		}
	printf("hello 1\n");


		// Set the value of u at the origin (to use better method later)
		// s->umr.u[0]=s->umr.u[1];
		if(A0==0) s->umr.u[0]=u0(&s->umr);
		// Filter u, m and r
		filterm(s->umr.u);
		filterm(s->umr.m);
		filterm(s->umr.r);
		// Fix boundary conditions
		if(A0==0) {
			s->umr.m[0]=0;
			s->umr.r[0]=0;
		}
		// Will need to fix u boundary condition later too

		// Whole bunch of pinning that didn't work out so well
		// s->umr.m[N] = s->umr.r[N] / (s->t * s->t * 8);
		// s->umr.u[N] = 1/(2*s->t);
		// s->umr.r[N] = s->Afrw * sqrt(s->t*sqrt(32*M_PI_3));
		// printf("%d\t%d\t%f\n",i++,j,s->t);

		// Check for black hole formation
		if(blackholeQ(&s->umr)!=-1){
			// fprintf(stderr, "black hole! at %f\n",AFRW*.5*(1-cos(M_PI*blackholeQ(&s->umr)/N)));
			return 1;
		}


		if(s->umr.photon>1)
			break;
	// printf("something 4els%e\n", h);


	}

	//Collect u,m,r,A,t where the photon is.
	umrat[0] = chebInterp(s->umr.u,s->umr.photon*2-1);
	umrat[1] = chebInterp(s->umr.m,s->umr.photon*2-1);
	umrat[2] = chebInterp(s->umr.r,s->umr.photon*2-1);
	umrat[3] = s->umr.photon + (1-s->umr.photon) * A0/AFRW;
	umrat[4] = s->t;

	if (s->umr.photon > .3 && A0 < .5 * AFRW){
		// fprintf(stderr, "Regridding\n");
		regrid(s);
	}

	printf("%e\n",h);

	if(s->umr.photon>1){
			fprintf(stderr, "photon hit the boundary: %f > 1\n", s->umr.photon);
			return 8;
		}

	// Check if a black hole is not going to form: if all densities < 1% of original FRW density
	// Obtain rho
	resvar res;
	update(s->t,&s->umr,&res);
	i=N+1; while(i-->0){
		if(res.rho[i]>0.000001) return 0;
	}

	// If we got to here, we have no overdensities to speak of
	fprintf(stderr, "No black hole forming.\n");
	return 1;

}

// Set up everything. Only needs to be called once.
// a is the rebasing size
void msSetup(double a){
	// Spectral setup
	spectSetup(RATIO=a);
	// GSL ODE_INT setup
	step = gsl_odeiv2_step_alloc(gsl_odeiv2_step_rkf45, 3*(N+1)+1);
	con = gsl_odeiv2_control_y_new(1E-10, 1E-7); // Tiny absolute, larger relative
	// con = gsl_odeiv2_control_y_new(1E-6,0);
	eve = gsl_odeiv2_evolve_alloc(3*(N+1)+1);
}

// Routine to release the GSL allocated memory
void msRelease(){
// GSL ODE_INT release
	gsl_odeiv2_evolve_free(eve);
	gsl_odeiv2_control_free(con);
	gsl_odeiv2_step_free(step);
}

// Boundary condition hack: set up the underdensity at the outer boundary
void bcHack(double *m, double mFRW){
	double a[N+1];
	double ma[N+1];
	//do some integration
	int i;
	i=N+1; while(i-->0) a[i]=0;
	// a[N-2]=1;
	// a[N-3]=7;
	// a[N-4]=21;
	// a[N-5]=35;
	// a[N-6]=35;
	// a[N-7]=21;
	// a[N-8]=7;
	// a[N-9]=1;

	a[N-12]=1;
	a[N-13]=7;
	a[N-14]=21;
	a[N-15]=35;
	a[N-16]=35;
	a[N-17]=21;
	a[N-18]=7;
	a[N-19]=1;


	intm(a,ma);

	//ma[N] alpha + m[N] == mFRW
	// ==> alpha = (mFRW - m[N]) / ma[N].

	a[0] = (mFRW - m[N]) / ma[N];

	i=N+1; while(i-->0){
		m[i] += ma[i] * a[0];
	}
}

// Initializes everything. Needs to be called for each evolution.
// Takes R, rho and u initial data, and constructs everything else
// Modifies rho to enforce matching condition
void msInit(state *s){
	int i;
	// Dynamic variables and rest
	dynvar *umr=&s->umr;
	resvar *res=&s->res;

	// Photon initial position
	umr->photon = 0;

	// Derivative of R
	ddxm(umr->r,res->dr);

	// Calculate m'
	i=N+1; while(i-->0){
		//temporarily store m' in \Gamma
		res->gamma2[i] = 4 * M_PI * res->rho[i] * umr->r[i] * umr->r[i] * res->dr[i];
	}
	// Calculate m (note: little m, not big M)
	intm(res->gamma2,umr->m);

	// Create M = m/r^2
	i=N+1; while(i-->1){
		umr->m[i] /= umr->r[i] * umr->r[i];
	}

	// Calculate the mass overdensity.
	double over = chebInterp(umr->m,(2/umr->r[N])-1);
	fprintf(stderr, "mass overdensity: %f\n", over/(4 * M_PI_3) - 1);

	// Enforce the matching condition
	bcHack(umr->m, 4 * M_PI_3 * umr->r[N]);

	// Enforce the boundaries of the initial data
	umr->m[0]=0;
	umr->m[N]=4 * M_PI_3 * umr->r[N];

	// Fix the starting time
	s->t = sqrt(M_1_PI * 3 / 32);
	// Outer boundary at starting time (how many horizons we span initially)
	AFRW = umr->r[N];
	A0=0;

        // Calculate rho, gamma, etc from u, m and r
        update(s->t, &s->umr, &s->res);
}
