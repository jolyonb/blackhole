#include <math.h>
#include "spect.h"

typedef struct dynvar {
  double u[N];
  double r[N];
  double m[N];
  dplan rDiff;
  dplan mDiff;
} dynvar;

typedef struct state {
  //variables to track
  /* double u[N]; */
  /* double r[N]; */
  /* double m[N]; */
  dynvar umr;
  dynvar umra;
  double gamma2[N]; // gamma^2
  double rho[N];
  double phi[N];

  //some derivatives
  double dr[N];
  double drho[N];

  //derivative and integral plans
  //dplan rDiff;
  //dplan rDiffa;
  dplan rhoDiff;
  dplan phiInt;
  //dplan mDiff;
} state;

void msSetup(state *s){
  mkwi();
  s->umr.rDiff.yin=s->umr.r;
  s->umr.rDiff.yout=s->dr;
  s->umra.rDiff.yin=s->umra.r;
  s->umra.rDiff.yout=s->dr;
  s->rhoDiff.yin=s->rho;
  s->rhoDiff.yout=s->drho;
  s->phiInt.yin=s->phi;
  s->phiInt.yout=s->phi;
  s->umr.mDiff.yin=s->umr.m;
  s->umr.mDiff.yout=s->rho; //yess, this is hacky. I think it'll be okay.
  s->umra.mDiff.yin=s->umra.m;
  s->umra.mDiff.yout=s->rho;
  plddx(&s->umr.rDiff);
  plddx(&s->umra.rDiff);
  plddx(&s->rhoDiff);
  plint(&s->phiInt);
  plddx(&s->umr.mDiff);
  plddx(&s->umra.mDiff);
}
  
//Equations of motion.

inline static double dudt(double phi, double r, double dr, double gamma2, double rho, double drho, double m){
  return -1*exp(phi)*(gamma2*r*r*drho/(dr*4*rho)+m/(r*r)+4*M_PI*r*rho/3);
}

inline static double drdt(double phi, double u){
  return exp(phi)*u;
}

inline static double dmdt(double phi, double rho, double r, double u){
  return -1*exp(phi)*4*M_PI*rho*r*r*u/3;
}

inline static double gam2(double u, double m, double r){
  return 1+u*u-(2*m)/r;
}

inline static double rho(double r, double dr, double dm){
  return dm/(4*M_PI*r*r*dr);
}



/* inline static double dudt(const state * restrict s, const dynvar * restrict umr, int i){ */
/*   return -1 * exp(s->phi[i]) * \ */
/*     (s->gamma2[i] * umr->r[i] * umr->r[i] * s->drho[i] / (4 * s->dr[i] * s->rho[i])\ */
/*     + umr->m[i]/(umr->r[i] * umr->r[i]) + 4 * M_PI * umr->r[i] * s->rho[i] / 3); */
/* } */

/* inline static double drdt(const state * restrict s, const dynvar * restrict umr, int i){ */
/*   return exp(s->phi[i]) * umr->u[i]; */
/* } */

/* inline static double dmdt(const state * restrict s, const dynvar * restrict umr, int i){ */
/*   return -4 * M_PI * exp(s->phi[i]) * s->rho[i] * umr->r[i] * umr->r[i] * umr->u[i] / 3; */
/* } */

/* inline static double gam2(const dynvar * umr, int i){ */
/*   return 1 + umr->u[i] * umr->u[i] - (2 * umr->m[i]) / umr->r[i]; */
/* } */

/* inline static double rho(const state * restrict s, const dynvar * restrict umr, int i){ */
/*   return s->rho[i] / (4 * M_PI * umr->r[i] * umr->r[i] * s->dr[i]); //rho here is dm */
/* } */

static void ev(const state * restrict s1, const dynvar * restrict umrin, dynvar * restrict umrout, double dt){
  // ev() evolves the time derivative equatinos.

  // hm. might be worth putting u,r,m in their own struct.

  int i;
  double u5[N],r5[N];
  double h;

  i=N; while(i-->0){

    h=dudt(s1->phi[i], umrin->r[i], s1->dr[i], s1->gamma2[i], s1->rho[i], s1->drho[i], umrin->m[i]);
    u5[i] = s1->umr.u[i] + .5 * dt * h;
    umrout->u[i] = s1->umr.u[i] + dt * h;
    
    h = drdt(s1->phi[i],u5[i]);
    r5[i] = s1->umr.r[i] + .5 * dt * h;
    umrout->r[i] = s1->umr.r[i] + dt * h;

    h = dmdt(s1->phi[i],s1->rho[i],r5[i],u5[i]);
    umrout->m[i] = s1->umr.m[i] + dt * h;
  }
}

static void update(state * restrict s, dynvar * restrict umr){
  // runs the equations which are not time derivatives
  
  //double dphi[N];
  int i;

  i=N;
  while(i-->0){
    s->gamma2[i]=gam2(umr->u[i],umr->m[i],umr->r[i]);
  }

  //TODO: setting boundary conditions will have to happen in some fashion. Details TBD. (insert physics here as needed).
  umr->rDiff.b=0; //TODO: b.c.
  umr->mDiff.b=0; //TODO: b.c.
  
  exddx(&umr->rDiff);
  exddx(&umr->mDiff); //N.B. output is rho.
  
  i=N;while(i-->0){
    s->rho[i]=rho(umr->r[i],s->dr[i],s->rho[i]);
    //s->rho[i]=rho(s,i);
  }

  s->rhoDiff.b=0; //TODO: b.c.
  exddx(&s->rhoDiff);

  i=N;while(i-->0){
    s->phi[i]=s->drho[i]/(-4*s->rho[i]);
  }

  s->phiInt.b=0; //TODO: b.c.
  exint(&s->phiInt);
}

void msStep(state *s, double dt){  
  ev(s,&s->umr,&s->umra,.5*dt);
  update(s,&s->umra);
  ev(s,&s->umra,&s->umr,dt);
}

void msInit(){
  //Function to create state from initial conditions.
}
    



