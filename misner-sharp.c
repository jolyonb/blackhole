#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include "spect.h"

#define M_PI_3 1.0471975511965977462

typedef struct dynvar {
  double u[N+1];//New u = U/R
  double m[N+1];//New m= m/R^2
  double r[N+1];
  double photon;
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
  double Afrw;
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
  return 8 * M_PI_3 + umr->r[i] * ( umr->u[i] * umr->u[i] * umr->r[i] - 2 * umr->m[i]);
}

/*****/
static void update(double t, const dynvar * restrict umr, resvar * restrict s){
  // runs the equations which are not time derivatives
  
  double irhoFRW;
  int i;

  //s->gamma2[N] = 8 * M_PI_3;
  i=N; while(i-->1){
    s->gamma2[i]=gamma2(umr,s,i);
  }
  
  ddxm(umr->r,s->dr);
  ddxm(umr->m,s->rho);
  
  //  s->dr[N]=s->dr[N-1];
  
  i=N+1; while(i-->1){
      s->rho[i]=rho(umr,s,i);
  }

  s->rho[0]=s->rho[0]/(4*M_PI_3*s->dr[0]);
  irhoFRW = t * t * M_PI_3 * 32;
  s->rho[N]=1/irhoFRW;
  filterm(s->rho);
  filterm(s->gamma2);

  ddxm(s->rho,s->drho);
  
  //s->drho[N]=0;
  //s->drho[N]=s->drho[N-1];

  s->phi[N]=1;
  i=N; while(i-->0){
    s->phi[i]=pow(s->rho[i]*irhoFRW,-.25);
  }
  filterm(s->rho);
  // ddxm(s->rho,s->drho);
  filterm(s->phi);
  s->phi[N]=1;
}

/* Integrator */
/* dydt = function(y) */
int function(double t, const double y[], double dydt[], void * params){
  //printf("call at t = %f\n",t);
  int i;
  resvar stuff; //maxbe make this params.
  dynvar *umr = (void *) y;

  update(t,umr,&stuff);

  //  i=N; while(i-->1){
  //if (stuff.gamma2[i]<0)
  //   return GSL_FAILURE;
  //}

  //filterm(stuff.rho);
  // filterm(stuff.phi);
  // filterm(stuff.gamma2);

  i=N+1; while(i-- > 1){
    dydt[i]=dudt(umr,&stuff,i);
    dydt[i+N+1]=dmdt(umr,&stuff,i);
    dydt[i+2*N+2]=drdt(umr,&stuff,i);
  }
  
  //dydt[N] = -1/(2*t*t);
  // dydt[N+N+1] = umr->r[N]/(2*t);
  // dydt[3*N+2] = -3 * umr->m[N] / (2 * t);

  dydt[0]=0;
  dydt[N+1]=0;
  dydt[2*N+2]=0;

  dydt[3*N+3] = 0;

  return GSL_SUCCESS;
}

const gsl_odeiv2_system sys = {&function, NULL, 3*(N+1)+1, NULL};
gsl_odeiv2_step * step;
gsl_odeiv2_control * con;
gsl_odeiv2_evolve * eve;
//gsl_odeiv2_driver *driver;

int blackholeQ(dynvar *umr){
  int i;
  int ready=0;
  for(i=0; i<N+1; i++){
    if (umr->m[i] * umr->r[i] > 4 * M_PI_3) ready=1;
    if (umr->m[i] * umr->r[i] < 4 * M_PI_3 && ready ==1) return i;
  }
  return -1;
}

int msEvolve(state *s, double t1){
  //  gsl_odeiv2_driver_apply(driver, &s->t, t1, (void *) &s->umr);
  static double h=1E-3;
  int i=0,j;
  while(s->t<t1){
    j=gsl_odeiv2_evolve_apply(eve, con, step, &sys, &s->t, t1, &h, (void *) &s->umr);
    // filterm(s->umr.u);
    // s->umr.m[N] = s->umr.r[N] / (s->t * s->t * 8);
    s->umr.u[0]=s->umr.u[1];
    filterm(s->umr.u);
    filterm(s->umr.m);
    filterm(s->umr.r);
    s->umr.m[0]=0;
    s->umr.r[0]=0;


    // s->umr.r[N]=s.Afrw*sqrt()
    // s->umr.m[N] = s->umr.r[N] / (s->t * s->t * 8);
    // s->umr.u[N] = 1/(2*s->t);
    // printf("%d\t%d\t%f\n",i++,j,s->t);
    // s->umr.r[N] = s->Afrw * sqrt(s->t*sqrt(32*M_PI_3));
    //    s->umr.m[N] = 4 * M_PI_3 * s->umr.r[N] * s->

    //filterm(s->umr.u);
  }
  if(blackholeQ(&s->umr)!=-1){
      fprintf(stderr, "black hole! at %f\n",s->Afrw*.5*(1-cos(M_PI*blackholeQ(&s->umr)/N)));
      return 1;
    } 
  return 0;
}

void msSetup(double a){
  spectSetup(a);
  //driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk2, 1E-3, 1E-6, 0.0);
  //  gsl_odeiv2_driver_set_hmax(driver, 1E-6);
  step = gsl_odeiv2_step_alloc(gsl_odeiv2_step_rk2, 3*(N+1)+1);
  con = gsl_odeiv2_control_y_new(1E-10, 1E-6);
  eve = gsl_odeiv2_evolve_alloc(3*(N+1)+1);
}


void bcHack(double *m, double mFRW){
  double a[N+1];
  double ma[N+1];
  //do some integratino
  int i;
  i=N+1; while(i-->0) a[i]=0;
  // a[N-1]=1;
  a[N-2]=1;
  a[N-3]=2;
  a[N-4]=2;
  a[N-5]=1;

  intm(a,ma);

  //ma[N] alpha + m[N] == mFRW
  // ==> alpha = (mFRW - m[N]) / ma[N].

  a[0] = (mFRW - m[N]) / ma[N];
  
  i=N+1; while(i-->0){
    m[i] += ma[i] * a[0];
  }  
}

/*
void bcHack(double * r, double * dr, double * rho, double * m){
  //computes M using our underdensity bump hack.

  int i;
  double t[N+1];

  rho[N]=1;
  rho[N-1]=1;
  rho[N-2]=1;
  rho[N-3]=1;
  rho[N-4]=1;

  i=N+1; while(i-->0){
    t[i] = 4 * M_PI * rho[i] * r[i] * r[i] * dr[i];
  }

  intm(t,m);

  i=N+1; while(i-->0){
    m[i] /= r[i] * r[i];
    t[i] = 0;
  }
  t[N-1]=1;
  t[N-2]=1.5;
  t[N-3]=1;

  i=N+1; while(i-->0){
    t[i] = 4 * M_PI * t[i] * r[i] * r[i] * dr[i];
  }

  intm(t,rho);

  i=N+1; while(i-->0){
    rho[i] /= r[i] * r[i];
  }
  rho[0]=0;
  // filterm(rho);
  
  t[0] = (4 * M_PI_3 * r[N] - m[N]) / rho[N];

  i=N+1; while(i-->0){
 printf("%f\n",rho[i]);
    m[i] += t[0] * rho[i];
  }
}
*/
  

void msInit(state *s){
  //Function to create state from initial conditions, (U, R, rho).
  int i;
  dynvar *umr=&s->umr;
  resvar *res=&s->res;

  umr->photon = 0;
  
  ddxm(umr->r,res->dr);

  
  //alpha magic here. //or maybe later...
  //res->rho[N]=1;
  // res->rho[N-4]=1;
  i=N+1; while(i-->0){
    //temporarily store m' in \Gamma
    res->gamma2[i] = 4 * M_PI * res->rho[i] * umr->r[i] * umr->r[i] * res->dr[i];
    //    umr->m[i]=4*M_PI_3*umr->r[i]*res->rho[i];
  }
  intm(res->gamma2,umr->m);

  // bcHack(umr->m, 4 * M_PI_3 * umr->r[N] * umr->r[N] * umr->r[N]);
  

  i=N+1; while(i-->1){
    //M = m/r^2
    umr->m[i] /= umr->r[i] * umr->r[i];
  }

  // filterm(umr->m);
  double tempm[N+1];
  i=N+1;while(i-->0) tempm[i]=umr->m[i];
  rebasem(tempm);
  fprintf(stderr, "mass over density: %f\n", tempm[0]/(4 * M_PI_3) - 1);

  bcHack(umr->m, 4 * M_PI_3 * umr->r[N]);
  
  //bcHack(umr->r,res->dr,res->rho,umr->m);

  umr->m[0]=0;
  umr->m[N]=4 * M_PI_3 * umr->r[N];

  s->t = sqrt(M_1_PI * 3 / 32);
  s->Afrw = umr->r[N];
  res->phi[N]=1;
  res->gamma2[N]=8*M_PI_3;
  //  irhoFRW = t * t * M_PI_3 * 32;
  i=N; while(i-->0){
    res->gamma2[i]=gamma2(umr,res,i);
    res->phi[i]=pow(res->rho[i],-.25);
  } 
}