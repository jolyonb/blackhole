/*
 * Entry point of the program. Currently used to test the routines.
 *
 * Houses main and a print routine.
 *
 */

#include <stdio.h>
#include <math.h>
#include <fftw3.h> // Fastest fourier transform in the west
#include "misner-sharp.c" // Routines for evolution of the Misner-Sharp

static double x[N+1]; // The A values on the grid

// Takes a state, prints out a block of data of all the variables
void printstate(state data){
	int j;
	printf("#A\t\tu\t\tm\t\tr\t\trho\t\tphi\t\tgamma^2\t\tr'\t\trho'\t\tphot\n");
	for(j=0;j<(N+1);j++){
		printf("%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\n",.5+.5*x[j],data.umr.u[j],data.umr.m[j],data.umr.r[j],data.res.rho[j],data.res.phi[j],data.res.gamma2[j],data.res.dr[j],data.res.drho[j],data.umr.photon*AFRW,chebInterp(data.res.rho,data.umr.photon*2-1));
	}
}

// Entry point
int main(){
	// Number of points
	int i=N+1;

	// Used in debugging
	double y[i];
	double dy[i];
	double y1[i]; // For analytic comparisons

	// Variable definitions
	int j; // Random iterator
	state data; // Actual state of the system
	double to; // t_0 -> initial time
	fftw_plan p; // Plan for the the FFTs

	// Initialize matrices for integrals, derivatives, integrator, etc
	msSetup(0.8);

	// Loop backwards to initialize: gridpoints, R, rho and u
	while(i-- > 0) {
		// Gridpoints
		x[i]=-cos(M_PI*(i)/N);

		// Data: r, rho, u
		data.umr.r[i]=.5*(1+x[i])*5;
		data.res.rho[i]=1.0+1.9*exp(-.5*(data.umr.r[i]/(.5))*(data.umr.r[i]/(.5)));
		data.umr.u[i] = sqrt(8*M_PI_3);
	}

	// Construct the plan to grab data and output derivative
	p=fftw_plan_r2r_1d(N+1,data.res.rho,y,FFTW_REDFT00,FFTW_ESTIMATE);

	// Initialises the rest of the data (namely, m)
	msInit(&data);

	// Set initial time
	to=sqrt(3*M_1_PI/(32));

	// Calculate rho, gamma, etc from u, m and r
	update(data.t, &data.umr, &data.res);

	// Take 2000 steps
	i=2000;

	// The loop that does the evolution
	while(i-->0){

		// Do the timestep
		if(msEvolve(&data,data.t*1.005)!=0) {
			fprintf(stderr, "breaking\n");
			break;
		}

		// Go and updates values so that we can print them
		update(data.t, &data.umr, &data.res);

		printstate(data);
		printf("\n\n");

		// Computes and prints the coefficients in the density profile (debugging)
/*
		fftw_execute(p);
		for(j=0;j<=N;j++){
			printf("%e\n",y[j]);
		}
*/
		// Counter for the purposes of how well things are going
		//fprintf(stderr, "i=%d\n", i);
	}

	// Finished. Phew.
	return 0;
}
