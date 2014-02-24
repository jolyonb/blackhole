#include <math.h>
#include "spect.h"

#define M_PI_3 1.0471975511965977462

typedef struct dynvar {
//Might want these to be N+2 for alignment.
  double u[N+1];//New u = U/R
  double r[N+1];
  double m[N+1];//New m= m/R^2
  //dplan rDiff;
  //dplan mDiff;
} dynvar;

typedef struct state {
  //variables to track
  dynvar umr; //dynamic variables.
  double gamma2[N+1]; // gamma^2
  double rho[N+1];
  double phi[N+1]; //exp(phi)

  //some derivatives
  double dr[N+1];
  double drho[N+1];

  //derivative and integral plans
  //dplan rhoDiff;

  //  double l; //b-a
} state;

static dynvar K1; //memory for integrator.
//static dplan mInt; //for setting i.c.

void msSetup(double a){
  spectSetup(a);

  /*
  s->umr.rDiff.yin=s->umr.r;
  s->umr.rDiff.yout=s->dr;
  K1.rDiff.yin=K1.r;
  K1.rDiff.yout=s->dr;
  s->rhoDiff.yin=s->rho;
  s->rhoDiff.yout=s->drho;
  s->umr.mDiff.yin=s->umr.m;
  s->umr.mDiff.yout=s->rho; //yess, this is hacky. I think it'll be okay.
  K1.mDiff.yin=K1.m;
  K1.mDiff.yout=s->rho;
  mInt.yin=s->umr.m;
  mInt.yout=s->umr.m;

  plddx(&s->umr.rDiff);
  plddx(&K1.rDiff);
  plddx(&s->rhoDiff);
  plddx(&s->umr.mDiff);
  plddx(&K1.mDiff);
  plint(&mInt);
  */
}
  
//Equations of motion.
/*
inline double dudt(double phi, double r, double dr, double gamma2, double rho, double drho, double m, double u){
  return -1*phi*(gamma2*drho/(dr*4*rho*r)+m/r+4*M_PI_3*rho+u*u);
}

inline double drdt(double phi, double u, double r){
  return phi*u*r;
}

inline double dmdt(double phi, double rho, double r, double u, double m){
  return -1*phi*u*(4*M_PI_3*rho*r + 2 * m);
}

inline double gam2(double u, double m, double r){
  //returns \Gamma ^ 2
  return 1+r*(u*u*r-(2*m));
}

inline double rho(double r, double dr, double m, double dm){
  return (dm/(2*dr)+m/r)*1/(2*M_PI);//gotta work out r=0;
}
*/

inline static double dudt(const state *s, const dynvar *umr, int i){
  return -1 * s->phi[i] * \
    ( ( s->gamma2[i] * s->drho[i] ) / ( 4 * s->rho[i] * s->dr[i] * umr->r[i]) \
      + umr->m[i] / umr->r[i] + 4 * M_PI_3 * s->rho[i] + umr->u[i] * umr->u[i] );
}

inline static double dmdt(const state *s, const dynvar *umr, int i){
  return -2 * s->phi[i] * ( 2 * M_PI_3 * umr->r[i] * s->rho[i] + umr->m[i] );
}

inline static double drdt(const state *s, const dynvar *umr, int i){
  return s->phi[i] * umr->u[i] * umr->r[i];
}

inline static double rho(state *s, dynvar *umr, int i){
  //M' is stored in rho when this is called.
  return .25 * M_1_PI * ( s->rho[i] / s->dr[i] + 2 * umr->m[i] / umr->r[i]);
}

inline static double gamma2(state *s, dynvar *umr, int i){
  //returns \Gamma^2.
  return 1 + umr->r[i] * ( umr->u[i] * umr->u[i] * umr->r[i] - 2 * umr->m[i]);
}

static void ev(const state * restrict s1, const dynvar * restrict umrin, dynvar * restrict umrout, double dt){
  // ev() evolves the time derivative equatinos.

  int i;
  double u5[N+1],r5[N+1];
  double h;

  i=N+1; while(i-->1){
    //might want 3 loops here.

    //h=dudt(s1->phi[i], umrin->r[i], s1->dr[i], s1->gamma2[i], s1->rho[i], s1->drho[i], umrin->m[i], umrin->u[i]);
    h=dudt(s1,umrin,i);
    u5[i] = s1->umr.u[i] + .5 * dt * h;
    umrout->u[i] = s1->umr.u[i] + dt * h;
    
    //h = drdt(s1->phi[i],u5[i],umrin->r[i]);
    h=drdt(s1,umrin,i);
    r5[i] = s1->umr.r[i] + .5 * dt * h;
    umrout->r[i] = s1->umr.r[i] + dt * h;

    // h = dmdt(s1->phi[i],s1->rho[i],r5[i],u5[i], umrin->m[i]);
    h=dmdt(s1,umrin,i);
    umrout->m[i] = s1->umr.m[i] + dt * h;
  }

  umrout->u[0]=0;
  umrout->m[0]=0;
  umrout->r[0]=0;
}

static void update(state * restrict s, dynvar * restrict umr){
  // runs the equations which are not time derivatives
  
  double iphiN;
  int i;

  i=N+1; while(i-->1){
    //    s->gamma2[i]=gam2(umr->u[i],umr->m[i],umr->r[i]);
    s->gamma2[i]=gamma2(s,umr,i);
  }
  
  ddxm(umr->r,s->dr);  
  ddxm(umr->m,s->rho);
  
  i=N+1; while(i-->1){
    //    printf("%f\n",s->dr[i]);
    s->rho[i]=rho(s,umr,i);
    //s->rho[i]=rho(s,i);
  }
  s->rho[0]=s->rho[0]/(4*M_PI_3*s->dr[0]);
  /* s->rhoDiff.b=0; //TODO: b.c. */
  //exddx(&s->rhoDiff);

  ddxm(s->rho,s->drho);

  iphiN=pow(s->rho[N],.25);
  i=N; while(i-->0){
    s->phi[i]=pow(s->rho[i],-.25) * iphiN;
  }
}

void msStep(state *s, double dt){
  
  update(s,&s->umr);
  ev(s,&s->umr,&K1,.5*dt);
  update(s,&K1);
  ev(s,&K1,&s->umr,dt);
  //  update(s,&s->umr);
  //Only need to rescale U,m,R on the fly. the rest will be updated in the next pass.
}

void msInit(state *s){
  //Function to create state from initial conditions, (U, R, rho).
  int i;
  double iphiN;
  
  ddxm(s->umr.r,s->dr);

  i=N+1; while(i-->0){
    //temporarily store m' in \Gamma
    s->gamma2[i] = 4 * M_PI * s->rho[i] * s->umr.r[i] * s->umr.r[i] * s->dr[i];
  }
  intm(s->gamma2,s->umr.m);

  i=N+1; while(i-->1){
    //M = m/r^2
    s->umr.m[i] /= s->umr.r[i] * s->umr.r[i];
  }
  s->umr.m[0]=0;

  s->phi[N]=1;
  //might be done in an update();
  iphiN=pow(s->rho[N],.25);
  s->gamma2[N]=gamma2(s,&s->umr,N);
  i=N; while(i-->0){
    s->gamma2[i]=gamma2(s,&s->umr,i);
    s->phi[i]=pow(s->rho[i],-.25) * iphiN;
  }
  s->gamma2[0]=1;
}
    



