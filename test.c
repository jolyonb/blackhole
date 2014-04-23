#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include "misner-sharp.c"
//#include "spect.c"

static double x[(N+1)*3];
void printstate(state meee){
  int j;
  printf("#A\t\tu\t\tm\t\tr\t\trho\t\tphi\t\tgamma^2\t\tr'\t\trho'\t\tphot\n");
  for(j=0;j<(N+1);j++){
     printf("%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\t%#.6e\n",.5+.5*x[j],meee.umr.u[j],meee.umr.m[j],meee.umr.r[j],meee.res.rho[j],meee.res.phi[j],meee.res.gamma2[j],meee.res.dr[j],meee.res.drho[j],meee.umr.photon*AFRW,chebInterp(meee.res.rho,meee.umr.photon*2-1));
  }
}

int main(){
  // mkwi();
  //double x[(N+1)*3];
  double y[(N+1)*3];
  double y1[(N+1)*3];
  double dy[(N+1)*3];
  int i=(N+1);
  int j;
  state meee;
  double to;
  fftw_plan p;
  //flyplan fpl;
  //fpl.y=y;
  //fpl.n=3;

  
  msSetup(0.8);

  // plint(&meee);
  //  plddx(&meee);
  //   plddxm();
  //plfly(&fpl);
  //plrebase(.5);
    i=N+1; while(i-->0){
      x[i]=-cos(M_PI*(i)/N);

      // x[i]=cos(.5*M_PI*(N-i)/N);
      // y[i]=0;
      // y1[i]=y[i]=x[i];
      //y1[i]=y[i]=sin(x[i])+cos(x[i]);
      // y1[i]=y[i]=pow(x[i],6);
      // dy[i]=y[i]=y1[i]=exp(x[i]);
      // y[i]=pow(x[i],15)/(N);
      //      y[i]=pow(x[i],N)/N;
      //y[i]=pow(x[i],N+1)/(N+1);
      //y[i]=cos((N-1)*i*M_PI/N);
      // y[i]=pow(x[i],5);
      y[i]=cos(M_PI*i);
      // y[i]=pow(x[i],2);
      // y[i]=pow(x[i]);
      //dy[i+N+1]=pow(x[i],N);
      // dy[i]=sin((1+x[i])*.8/2+.2)+cos((1+x[i])*.8/2+.2);
      //y[i]=-1+2*x[i]*x[i];
    //y[i]=sin(x[i])*(1-x[i]);
      meee.umr.r[i]=.5*(1+x[i])*5;
      meee.res.rho[i]=1.0+1.9*exp(-.5*(meee.umr.r[i]/(.5))*(meee.umr.r[i]/(.5)));
      //meee.umr.u[i]=1*sqrt(8*M_PI_3*meee.res.rho[i]);
      meee.umr.u[i] = sqrt(8*M_PI_3);
    //y[i]*=y[i];r
    }
    meee.umr.u[0]=0;
  /*  y[0]+=-N; */
  /* y1[0]+=-N; */
  /* y[N]+=N; */
  /*  y1[N]+=N; */
  // y[N-1]=1;
  //y[2]=0;
    p=fftw_plan_r2r_1d(N+1,meee.res.rho,y,FFTW_REDFT00,FFTW_ESTIMATE);
  
  

  //double m,a,fma;
  // intme(y,dy);
  msInit(&meee);

  // fftw_flops(fpl.p,&m,&a,&fma);
  // printf("%f\t%f\t%f\n",m,a,fma);
  // fftw_print_plan(meee.p[0]);
  //dplan das[2];
  //  printf("%d\n",sizeof(das));
  //  printf("%p\t%p\n",das,das+1);
  to=sqrt(3*M_1_PI/(32));
  i=1000;while(i-->0){
    //   msStep(&meee,.000001);
    //i%100==0?printf("%f\n",meee.t*meee.t*meee.rho[12]):1;
  }
  //   printf("%f\n",rho(meee.umr.r[N],meee.dr[N],meee.umr.m[N],meee.rho[N]));
  //printf("\n#u=U/R\t\tM=m/R^2\t\tR\t\trho\t\tphi\n");
  for(j=0;j<(N+1);j++){
    //    printf("%#.8g\t%#.8g\t%#.8g\t%#.8g\t%#.8g\t%#.8g\t%#.8g\n",meee.umr.u[j],meee.umr.m[j],meee.umr.r[j],meee.res.rho[j],meee.res.phi[j],meee.res.gamma2[j],meee.res.drho[j]);
  }
 
    
  update(meee.t, &meee.umr, &meee.res);
  // printstate(meee);

  //fprintf(stderr, "i=%d\n", i);



  // i=2000; while(i-->0){
  //   if(msEvolve(&meee,meee.t*1.005)!=0){
  //     fprintf(stderr, "breaking\n");
  //     break;
  //   }
  //   //   function(1,(void *) &meee.umr, y, NULL);
  //   //filterm(meee.umr.u);
  //   update(meee.t, &meee.umr, &meee.res);
  //   // printf("%f\n",meee.t*meee.t*meee.res.rho[1]);
  //   //    ddxm(meee.umr.m,y);

  //   //filterm(meee.res.dr);
  //   // filterm(meee.res.rho);
  //   fftw_execute(p);
  //   //printf("\n\n#u=U/R\t\tM=m/R^2\t\tR\t\trho\t\tphi\n");
  //   printf("\n\n");
  //   printstate(meee);
  //    // for(j=0;j<=N;j++){
  //    //   printf("%e\n",y[j]);
  //    // }
  //   fprintf(stderr, "i=%d\n", i);
  // }




  //fprintf(stderr, "i=%d\n", i);
  
  /*
  i=55; while(i-->0){
    msEvolve(&meee,meee.t*1.06);
    //   function(1,(void *) &meee.umr, y, NULL);
    update(meee.t, &meee.umr, &meee.res);
    // printf("%f\n",meee.t*meee.t*meee.res.rho[1]);
    //ddxm(meee.umr.m,y);
    //printf("\n\n#u=U/R\t\tM=m/R^2\t\tR\t\trho\t\tphi\n");
    printf("\n\n");
    printstate(meee);
  }
  */
  
  //update(meee.t, &meee.umr, &meee.res);

   // filterm(meee.res.rho);

  // printf("#u=U/R\t\tM=m/R^2\t\tR\t\trho\t\tphi\n");
  //filterm(y);
  for(i=0;i<(N+1);i++){
     printf("%e\t%e\t%e\n",x[i],y[i],chebInterp(y,x[i]));
  }
  //printf("%.19f\t%.19f\n",M_PI_3,1.0471975511965977462);
  //  printf("%p\t%p\t%p\n",meeee.umr.u,meeee.umr.m,meeee.umr.r);

  return 0;
}
