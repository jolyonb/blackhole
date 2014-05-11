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
#include <string.h> // Used for reading the parameter file
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h> // Used for interpolating to obtain initial data on the null slice

// Data type for describing a spline
struct splinetool {
	gsl_interp_accel *acc;
	gsl_spline *spline;
};

static double x[N+1]; // The A values on the grid

// Takes a state, prints out a block of data of all the variables
void printstate(state data){
	int j;
	printf("#A\t\tu\t\tm\t\tr\t\trho\t\tphi\t\tgamma^2\t\tr'\t\trho'\t\tphot\n");
	for(j=0;j<(N+1);j++){
		printf("%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\n",.5+.5*x[j],data.umr.u[j],data.umr.m[j],data.umr.r[j],data.res.rho[j],data.res.phi[j],data.res.gamma2[j],data.res.dr[j],data.res.drho[j],data.umr.photon*AFRW,chebInterp(data.res.rho,data.umr.photon*2-1));
	}
	printf("\n\n");
}

// Reads in a single parameter from the param.ini file
// The input "parameter" is a null terminated string
// params.ini is a list of parameter names, followed by a space and a number
double getparam(const char *parameter) {

	FILE *ifp;
	char *mode = "r";
	char paramname[17];  /* At most 16 characters, + one extra for null char. */
	double val;

	// Open the file
	ifp = fopen("params.ini", mode);

	// Check to make sure it's opened
	if (ifp == NULL) {
	  fprintf(stderr, "Fatal Error: Can't open params.ini.\n");
	  exit(1);
	}

	// Loop through the file, trying to find the parameter we want
	while (!feof(ifp)) {
		if (fscanf(ifp, "%s %lf", paramname, &val) == 2) {
			if (strncmp(parameter, paramname, 17) == 0) {
				// Found the parameter we're after.
				// Close the file
				fclose(ifp);
				// Return the value
				return val;
			}
		}
	}

	// Close the file
	fclose(ifp);

	// We couldn't find that parameter
	fprintf(stderr, "Fatal Error: Can't find parameter %s in params.ini.\n", parameter);
	exit(1);

	return 0.0;
}

// Entry point
int main(){

	// Used in debugging
	double y[N+1];
	double dy[N+1];
	double y1[N+1]; // For analytic comparisons

	// Variable definitions
	int i, j; // Random iterators
	state data; // Actual state of the system
	double umrat[2000][5]; //storage for null slice
	double to; // t_0 -> initial time
	fftw_plan p; // Plan for the the FFTs

	// Initialize matrices for integrals, derivatives, integrator, etc
	msSetup(0.8);

	// Read in the parameters for the density profile
	double amplitude = getparam("amplitude");
	double AFRW = getparam("AFRW");

	// Loop backwards to initialize: gridpoints, R, rho and u
	i=N+1; while(i-- > 0) {
		// Gridpoints
		x[i]=-cos(M_PI*(i)/N);

		// Data: r, rho, u
		// Note the last value in this expression for r gives how many horizon spans we have initially
		data.umr.r[i]=.5 * (1+x[i]) * AFRW;
		data.res.rho[i]=1.0 + amplitude * exp(-.5*(data.umr.r[i]/(.5))*(data.umr.r[i]/(.5)));
		data.umr.u[i] = sqrt(8*M_PI_3);
	}

	// Debugging
	i=N+1; while(i-- > 0){
		y[i]=cos(M_PI*i);
	}

	// Construct the plan to grab data and output derivative
	p=fftw_plan_r2r_1d(N+1,data.res.rho,y,FFTW_REDFT00,FFTW_ESTIMATE);

	// Initialises the rest of the data (namely, m)
	msInit(&data);

	// Calculate rho, gamma, etc from u, m and r
	update(data.t, &data.umr, &data.res);

	//inital photon stuff
	umrat[0][0]=data.umr.u[0];
	umrat[0][1]=0;
	umrat[0][2]=0;
	umrat[0][3]=0;
	umrat[0][4]=data.t;

	printf("%e\t%e\t%e\t%e\t%e\n", umrat[0][0],umrat[0][1],umrat[0][2],umrat[0][3],umrat[0][4]);


	// Take 2000 steps
	// The loop that does the evolution
	for(i=1;i<2000;i++){

		// Do the timestep
		if(msEvolve(&data,data.t*1.005,umrat[i])!=0) {
			fprintf(stderr, "Breaking\n");
			printf("\n\n");
			printstate(data);
			printf("%e\t%e\t%e\t%e\t%e\n", umrat[i][0],umrat[i][1],umrat[i][2],umrat[i][3],umrat[i][4]);
			break;
		}
		// fprintf(stderr, "u=%f\n",umrat[0] );

		// Go and updates values so that we can print them
		update(data.t, &data.umr, &data.res);

		printf("\n\n");
		printstate(data);

		printf("%e\t%e\t%e\t%e\t%e\n", umrat[i][0],umrat[i][1],umrat[i][2],umrat[i][3],umrat[i][4]);


		// Computes and prints the coefficients in the density profile (debugging)
/*
		fftw_execute(p);
		for(j=0;j<=N;j++){
			printf("%e\n",y[j]);
		}
*/
		// Counter for the purposes of how well things are going
		// fprintf(stderr, "i=%d\n", i);
	}


	// Now that we've gotten to here, we need to switch over to the null coordinate system.
	// Before doing so, we need to construct our initial data.
	// The initial data needs to be interpolated from the umrat arrays.
	// We'll use the GSL cubic spline interpolators to perform the interpolation.
	// Unfortunately, the umrat array can't be given to the interpolator directly, so we'll need to extract it
	// into individual arrays first.
	double idatu[2000];
	double idatm[2000];
	double idatr[2000];
	double idata[2000];
	double idatt[2000];
	for (j = 0; j < 2000; j++) {
		idatu[j] = umrat[j][0];
		idatm[j] = umrat[j][1];
		idatr[j] = umrat[j][2];
		idata[j] = umrat[j][3];
		idatt[j] = umrat[j][4];
	}
	int numrows = i + 1; // Number of rows of data in umrat

	// Initialize splines using A as the x variable, and y as m, r, t and u
	struct splinetool uspline;
	struct splinetool mspline;
	struct splinetool rspline;
	struct splinetool tspline;
	uspline.acc = gsl_interp_accel_alloc();
	mspline.acc = gsl_interp_accel_alloc();
	rspline.acc = gsl_interp_accel_alloc();
	tspline.acc = gsl_interp_accel_alloc();
	uspline.spline = gsl_spline_alloc(gsl_interp_cspline, numrows);
	mspline.spline = gsl_spline_alloc(gsl_interp_cspline, numrows);
	rspline.spline = gsl_spline_alloc(gsl_interp_cspline, numrows);
	tspline.spline = gsl_spline_alloc(gsl_interp_cspline, numrows);

	// Construct the splines
	gsl_spline_init (uspline.spline, idata, idatu, numrows);
	gsl_spline_init (mspline.spline, idata, idatm, numrows);
	gsl_spline_init (rspline.spline, idata, idatr, numrows);
	gsl_spline_init (tspline.spline, idata, idatt, numrows);

	// To get the value from a spline, use the following command
	// val = gsl_spline_eval (myspline.spline, a, myspline.acc);

	// Print out t at a = 1
	double val = gsl_spline_eval (tspline.spline, 1.0, tspline.acc);
	fprintf(stderr,"t at a = 1: %lf\n", val);
	double t0 = sqrt(1/(32*M_PI_3));
	fprintf(stderr, "delta t^1/2 = %f\n", (sqrt(val) - sqrt(t0))*2*sqrt(8*M_PI_3)*sqrt(t0));

	// Destroy the plan
	fftw_destroy_plan(p);

	// Release the GSL memory
	msRelease();

	// Finished. Phew.
	fprintf(stderr, "Done!\n");
	return 0;
}
