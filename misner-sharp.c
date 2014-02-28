#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "spect.h"

#define M_PI_3 1.0471975511965977462

typedef struct dynvar {
  double u[N+1];//New u = U/R
  double m[N+1];//New m= m/R^2
  double r[N+1];
} dynvar;

typedef struct resvar {
  double gamma2[N+1];
  double rho[N+1];
  double phi[N+1];

  double dr[N+1];
  double drho[N+1];
} resvar;

typedef struct state {
  //variables to track
  dynvar umr; //dynamic variables.
  resvar res;

  double t;
} state;


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
  //M' is stored in rho when this is called.
  return .25 * M_1_PI * ( s->rho[i] / s->dr[i] + 2 * umr->m[i] / umr->r[i]);
}

inline static double gamma2(const dynvar * restrict umr, const resvar * restrict s, int i){
  //returns \Gamma^2.
  return 1 + umr->r[i] * ( umr->u[i] * umr->u[i] * umr->r[i] - 2 * umr->m[i]);
}

/*****/
static void update(double t, const dynvar * restrict umr, resvar * restrict s){
  // runs the equations which are not time derivatives
  
  double irhoFRW;
  int i;

  i=N+1; while(i-->1){
    s->gamma2[i]=gamma2(umr,s,i);
  }
  
  ddxm(umr->r,s->dr);  
  ddxm(umr->m,s->rho);
  
  i=N+1; while(i-->1){
    s->rho[i]=rho(umr,s,i);
  }
  s->rho[0]=s->rho[0]/(4*M_PI_3*s->dr[0]);
  irhoFRW = t * t * M_PI_3 * 32;
  s->rho[N]=1/irhoFRW;

  ddxm(s->rho,s->drho);

  
  i=N+1; while(i-->0){
    s->phi[i]=pow(s->rho[i]*irhoFRW,-.25);
  }
}

/* Integrator */
/* dydt = function(y) */
int function(double t, const double y[], double dydt[], void * params){
  //printf("call at t = %f\n",t);
  int i;
  resvar stuff;
  dynvar *umr = (void *) y;
  update(t,umr,&stuff);

  i=N+1; while(i-- > 1){
    dydt[i]=dudt(umr,&stuff,i);
    dydt[i+N+1]=dmdt(umr,&stuff,i);
    dydt[i+2*N+2]=drdt(umr,&stuff,i);
  }
  dydt[0]=0;
  dydt[N+1]=0;
  dydt[2*N+2]=0;

  return GSL_SUCCESS;
}

const gsl_odeiv2_system sys = {&function, NULL, 3*(N+1), NULL};
gsl_odeiv2_driver *driver;

void msEvolve(state *s, double t1){;
  gsl_odeiv2_driver_apply(driver, &s->t, t1, (void *) &s->umr);
}

void msSetup(double a){
  spectSetup(a);
  driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk4, .001, 1E-6, 0.0);
}

void msInit(state *s){
  //Function to create state from initial conditions, (U, R, rho).
  int i;
  dynvar *umr=&s->umr;
  resvar *res=&s->res;
  double irhoFRW;
  
  ddxm(umr->r,res->dr);

  i=N+1; while(i-->0){
    //temporarily store m' in \Gamma
    res->gamma2[i] = 4 * M_PI * res->rho[i] * umr->r[i] * umr->r[i] * res->dr[i];
  }
  intm(res->gamma2,umr->m);

  i=N+1; while(i-->1){
    //M = m/r^2
    umr->m[i] /= umr->r[i] * umr->r[i];
  }
  umr->m[0]=0;

  s->t = sqrt(M_1_PI * 3 / 32);
  //s->phi[N]=1;
  //  irhoFRW = t * t * M_PI_3 * 32;
  i=N+1; while(i-->0){
    res->gamma2[i]=gamma2(umr,res,i);
    res->phi[i]=pow(res->rho[i],-.25);
  } 
}
    



