#include <math.h>
#include "spect.h"

typedef struct state {
  //variables to track
  double u[N];
  double r[N];
  double m[N];
  double gamma2[N]; // gamma^2
  double rho[N];
  double phi[N];

  //some derivatives
  double dr[N];
  double drho[N];

  //derivative and integral plans
  dplan rDiff;
  dplan rhoDiff;
  dplan phiInt;
  dplan mDiff;
} state;

void msSetup(state *s){
  mkwi();
  s->rDiff.yin=s->r;
  s->rDiff.yout=s->dr;
  s->rhoDiff.yin=s->rho;
  s->rhoDiff.yout=s->drho;
  s->phiInt.yin=s->phi;
  s->phiInt.yout=s->phi;
  s->mDiff.yin=s->m;
  s->mDiff.yout=s->rho; //yess, this is hacky. I think it'll be okay.
  plddx(&s->rDiff);
  plddx(&s->rhoDiff);
  plint(&s->phiInt);
  plddx(&s->mDiff);
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

void ev(state *s1, double * restrict u2, double * restrict r2, double * restrict m2, double dt){
  // ev() evolves the time derivative equatinos.

  // hm. might be worth putting u,r,m in their own struct.

  int i;
  double u5[N],r5[N];
  double h;

  i=N; while(i-->0){

    h=dudt(s1->phi[i], s1->r[i], s1->dr[i], s1->gamma2[i], s1->rho[i], s1->drho[i], s1->m[i]);
    u5[i] = s1->u[i] + .5 * dt * h;
    u2[i] = s1->u[i] + dt * h;
    
    h = drdt(s1->phi[i],u5[i]);
    r5[i] = s1->r[i] + .5 * dt * h;
    r2[i] = s1->r[i] + dt * h;

    h = dmdt(s1->phi[i],s1->rho[i],r5[i],u5[i]);
    m2[i] = s1->m[i] + dt * h;
  }
}

void update(state * restrict s, const double * restrict u, const double * restrict r, const double * restrict m){
  // runs the equations which are not time derivatives
  
  //double dphi[N];
  int i;

  i=N;
  while(i-->0){
    s->gamma2[i]=gam2(u[i],m[i],r[i]);
  }

  //TODO: setting boundary conditions will have to happen in some fashion. Details TBD. (insert physics here as needed).
  s->rDiff.b=0; //TODO: b.c.
  s->mDiff.b=0; //TODO: b.c.
  
  exddx(&s->rDiff);
  exddx(&s->mDiff); //N.B. output is rho.
  
  i=N;while(i-->0){
    s->rho[i]=rho(s->r[i],s->dr[i],s->rho[i]);
  }

  s->rhoDiff.b=0; //TODO: b.c.
  exddx(&s->rhoDiff);

  i=N;while(i-->0){
    s->phi[i]=s->drho[i]/(-4*s->rho[i]);
  }

  s->phiInt.b=0; //TODO: b.c.
  exint(&s->phiInt);
}

void step(state *s, double dt){  
  //integrator goes here.
}
    



