/*
 * Entry point of the program. Currently used to test the routines.
 *
 * Houses main and a print routine.
 *
 */

#include "test.h"

// Entry point
int main(int argc, char **argv){
	// Variable definitions
	int i,j; // Random iterators
	state data; // Actual state of the system
	double umrat[2000][5]; // Storage for null slice
	int result = 0; // Response from functions

/*
 ******************************* File Init *********************************
 */

	// Sort out the command line arguments
	char *outfilename = NULL;
	char name_default[] = "output";
	if (argc > 1) {
		// We have a command line argument. Assume it's a filename.
		outfilename = argv[1];
	} else {
		outfilename = name_default;
	}
	// Print a message about the output filenames
	printf("Outputting to files: %s-xxxx.dat\n", outfilename);

	// All the file handles we want to print to
	FILE *nullgeodesic;
	FILE *msdata;  // Misner-Sharp data
	FILE *nullinit;  // Misner-Sharp data
	// Open the files
	// Null geodesic first
	char filenamebuffer[1024];
	strcpy (filenamebuffer, outfilename);
	strcat (filenamebuffer, "-null.dat");
	nullgeodesic = fopen(filenamebuffer, "w");
	// Check to make sure that it was opened
	if (nullgeodesic == NULL) {
		fprintf(stderr, "Fatal Error: Can't open output file %s\n", filenamebuffer);
		exit(1);
	}
	// Print the header line
	fprintf(nullgeodesic, "#u\t\tM\t\tR\t\tA\t\tt\n");

	// Misner-Sharp data next
	strcpy (filenamebuffer, outfilename);
	strcat (filenamebuffer, "-ms.dat");
	msdata = fopen(filenamebuffer, "w");
	// Check to make sure that it was opened
	if (msdata == NULL) {
		fprintf(stderr, "Fatal Error: Can't open output file %s\n", filenamebuffer);
		exit(1);
	}

	// Null slice initial data output
	strcpy (filenamebuffer, outfilename);
	strcat (filenamebuffer, "-nullinit.dat");
	nullinit = fopen(filenamebuffer, "w");
	fprintf(nullinit, "#u\t\tM\t\tR\t\tA\t\tt\n");
	// Check to make sure that it was opened
	if (nullinit == NULL) {
		fprintf(stderr, "Fatal Error: Can't open output file %s\n", filenamebuffer);
		exit(1);
	}

/*
 ******************************* Data initialization *********************************
 */

	// Initialize matrices for integrals, derivatives, integrator, etc
	msSetup(0.8);

	// Read in the parameters for the density profile
	double amplitude = getparam("amplitude");
	double AFRW = getparam("AFRW");
	double timestep = getparam("timestep");
	int maxloop = getintparam("maxloop");

	// Loop backwards to initialize: gridpoints, R, rho and u
	i=N+1; while(i-- > 0) {
		// Gridpoints
		A[i]= 0.5 * (1 - cos(M_PI*(i)/N));

		// Data: r, rho, u
		// Note the last value in this expression for r gives how many horizon spans we have initially
		data.umr.r[i] = A[i] * AFRW;
		data.res.rho[i] = 1.0 + amplitude * exp(-.5*(data.umr.r[i]/(.5))*(data.umr.r[i]/(.5)));
		data.umr.u[i] = sqrt(8*M_PI_3);
	}

	// Initialises the rest of the data (namely, m)
	msInit(&data);

	//inital photon stuff
	umrat[0][0]=data.umr.u[0];
	umrat[0][1]=0;
	umrat[0][2]=0;
	umrat[0][3]=0;
	umrat[0][4]=data.t;

	// Used in debugging
	double y[N+1];
	double dy[N+1];
	double y1[N+1]; // For analytic comparisons
	fftw_plan p; // Plan for the the FFTs
	// Construct the plan to grab data and output derivative
	p=fftw_plan_r2r_1d(N+1,data.res.rho,y,FFTW_REDFT00,FFTW_ESTIMATE);

/*
 ******************************* Misner-Sharp Loop *********************************
 */

	// The loop that does the evolution
	// Take maxloop steps at most
	for(i=0;i<maxloop;i++){

		// Counter for the purposes of how well things are going (debugging)
//		printf("i=%d\n", i);

		// Computes and prints the coefficients in the density profile (debugging)
//		fftw_execute(p);
//		for(j=0;j<=N;j++){
//			printf("%e\n",y[j]);
//		}

		// And go and print them :-)
		// (Note that this also prints out initial data before any timesteps are made)
		printstate(data, msdata);
		printgeodesicdata(umrat, i, nullgeodesic);

		// Check the result of the previous timestep to see if we want out
		if(result!=0) break;

		// Take a timestep
		result = msEvolve(&data,data.t*timestep,umrat[i]);
	}

	// Release all file handles that are no longer necessary
	fclose(nullgeodesic);
	fclose(msdata);

	// Make a nice statement about why the loop terminated
	printf("Misner-Sharp Evolution ended: ");
	if (result == 1) {
		printf("Aborted due to error.\n");
	} else if (result == 8) {
		printf("Null geodesic hit outer boundary.\n");
	} else if (result == 2) {
		printf("Black hole formation detected.\n");
	} else {
		printf("Unknown reason.\n");
	}

/*
 ******************************* Null initialization *********************************
 */

	// Now that we've gotten to here, we need to switch over to the null coordinate system.
	// Before doing so, we need to construct our initial data.
	// i is the number of rows of data in umrat
	constructnulldata(umrat, i, &data);

	// Print the initial data on the null slice to file
	printnullinitdata(data, nullinit);
	// And close the file handle that is no longer necessary
	fclose(nullinit);


/*
 ******************************* Cleanup *********************************
 */

	// Destroy the plan
	fftw_destroy_plan(p);

	// Release the GSL memory
	msRelease();

	// Finished. Phew.
	printf("Done!\n");
	return 0;
}

// Constructs initial data on the null slice.
// umrat is the array of u, m, r, A and t variables that have been computed for the null geodesic.
// numrows is the number of rows that were used in umrat.
// data is where the initial data is placed.
void constructnulldata(double umrat[][5], int numrows, state *data) {

	int i;

	// The initial data needs to be interpolated from the umrat arrays.
	// We'll use the GSL cubic spline interpolators to perform the interpolation.
	// Unfortunately, the umrat array can't be given to the interpolator directly, so we'll need to extract it
	// into individual arrays first.
	double idatu[2000];
	double idatm[2000];
	double idatr[2000];
	double idata[2000];
	double idatt[2000];
	for (i = 0; i < 2000; i++) {
		idatu[i] = umrat[i][0];
		idatm[i] = umrat[i][1];
		idatr[i] = umrat[i][2];
		idata[i] = umrat[i][3];
		idatt[i] = umrat[i][4];
	}

//	dumparray(idatu, numrows, "dumpu.dat");
//	dumparray(idatm, numrows, "dumpm.dat");
//	dumparray(idatr, numrows, "dumpr.dat");
//	dumparray(idata, numrows, "dumpa.dat");
//	dumparray(idatt, numrows, "dumpt.dat");

	// Initialize splines using A as the x variable, and y as m, r, t and u
	spline uspline;
	spline mspline;
	spline rspline;
	spline tspline;
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

	// Next, we want to use our interpolators to intialize our data for umr on the null slice
	// Loop backwards to initialize: R, rho and u
	i=N+1; while(i-- > 0) {
		// Data: u, m, r
		data->umr.u[i] = gsl_spline_eval (uspline.spline, A[i], uspline.acc);
		data->umr.m[i] = gsl_spline_eval (mspline.spline, A[i], mspline.acc);
		data->umr.r[i] = gsl_spline_eval (rspline.spline, A[i], rspline.acc);
	}
	// Also set the time
	data->t = gsl_spline_eval (tspline.spline, 1.0, tspline.acc);
	// Reset the update flag on the rest of the data
	data->res.lastupdated = -1;

}

// Reads in a single parameter from the param.ini file
// The input "parameter" is a null terminated string
// params.ini is a list of parameter names, followed by a space and a number
double getparam(const char *parameter) {

	FILE *ifp;
	char paramname[17];  /* At most 16 characters, + one extra for null char. */
	double val;

	// Open the file
	ifp = fopen("params.ini", "r");

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

// Same as above, except it returns an integer
int getintparam(const char *parameter) {

	FILE *ifp;
	char paramname[17];  /* At most 16 characters, + one extra for null char. */
	int val;

	// Open the file
	ifp = fopen("params.ini", "r");

	// Check to make sure it's opened
	if (ifp == NULL) {
	  fprintf(stderr, "Fatal Error: Can't open params.ini.\n");
	  exit(1);
	}

	// Loop through the file, trying to find the parameter we want
	while (!feof(ifp)) {
		if (fscanf(ifp, "%s %d", paramname, &val) == 2) {
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

	return 0;
}

// Takes a state, prints out a block of data of all the variables to the appropriate file
void printstate(state data, FILE *handle){
	return;
	int j;
	fprintf(handle, "#A\t\tu\t\tm\t\tr\t\trho\t\tphi\t\tgamma^2\t\tr'\t\trho'\t\tphot\n");
	for(j=0;j<(N+1);j++){
		fprintf(handle, "%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\n",A[j]*(AFRW - A0) + A0,data.umr.u[j],data.umr.m[j],data.umr.r[j],data.res.rho[j],data.res.phi[j],data.res.gamma2[j],data.res.dr[j],data.res.drho[j],data.umr.photon*AFRW,chebInterp(data.res.rho,data.umr.photon*2-1));
	}
	fprintf(handle, "\n\n");
}

// Prints information on initial data on the null slice (A, u, m, r, t) to file
void printnullinitdata(state data, FILE *handle){
	return;
	int j;
	fprintf(handle, "#A\t\tu\t\tm\t\tr\t\tt = %#.6e\n", data.t);
	for(j=0; j<(N+1); j++){
		fprintf(handle, "%#.6e\t%#.6e\t%#.6e\t%#.6e\n",A[j],data.umr.u[j],data.umr.m[j],data.umr.r[j]);
	}

}

// Prints information on the null geodesic to file
void printgeodesicdata(double umrat[][5], int index, FILE *handle) {
	return;
	fprintf(handle, "%e\t%e\t%e\t%e\t%e\n", umrat[index][0],umrat[index][1],umrat[index][2],umrat[index][3],umrat[index][4]);

}

// Quick routine to dump an array to disc for debug purposes
// data is the array, num is the number of elements, and filename is self-explanatory ;-)
void dumparray(double *data, int num, const char *filename){
	FILE *ofp;

	// Open the file
	ofp = fopen(filename, "w");

	// Make sure it opened
	if (ofp == NULL) {
		fprintf(stderr, "Fatal Error: Can't open output file %s\n", filename);
		exit(1);
	}

	// Dump the data
	int j;
	for(j=0; j < num; j++){
		fprintf(ofp, "%#.6e\n", data[j]);
	}

	// Close the file
	fclose(ofp);
}
