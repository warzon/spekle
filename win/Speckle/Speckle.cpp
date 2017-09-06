// Speckle.cpp : Defines the entry point for the console application.
//

#include  <time.h>
#include	"park_miller.h"
#include	<stdlib.h>
#include	<math.h>
#include    <stdio.h>
#include    <time.h>

#define PARK_MILLER
//#define 
void  calculation_of_fi(void);
double x,y,s,z1,z2, rnm, rnm2, tmp, lg, srt, mu, sigma, fi, delta_fi,ksi;

 FILE *name1;

 void init(void)
{
}
 int main()
{
#ifdef PARK_MILLER
	Seed( time(NULL) );
#else
	srand( time(NULL) );
#endif
	if( (name1 = fopen("data11.dat", "w")) == NULL)
	{
		printf("can't open file! \n");
	}	
	calculation_of_fi();
	 fprintf(name1, "%g\n",delta_fi );
	 fclose (name1);

}

 void calculation_of_fi()
 {
	delta_fi=0;
	   fi=0;

/*#ifdef PARK_MILLER
	rnm1 = unirand2();
    if (rnm1 > 1.) rnm1 = 1.;
	if (rnm1 < 1e-10) rnm1 = 1e-10;
#else
	rnm1 = (double)rand()/32766.0;
	if (rnm1 > 1.) rnm1 = 1.;
	if (rnm1 < 1e-10) rnm = 1e-10;
#endif*/	  

	tmp=0;
rnm = (double)rand()/32766; 
if (rnm > 1) rnm = 1; 
if (rnm < 1e-30) rnm=1e-30;

//0<rnm<1 

x = rnm*2 - 1;
// -1<x<1

rnm2 = (double)rand()/32766; 
if (rnm2 > 1) rnm = 1; 
if (rnm2 < 1e-30) rnm=1e-30;
y = rnm2*2 - 1;

    
// #ifdef PARK_MILLER
	//x = unirand2();  
	//y = unirand2();
//#else
	//x = (double)rand()/32766.0;
	//y = (double)rand()/32766.0;
//#endif 

   	s = x*x + y*y;
 
 while ( s == 0 || s >= 1 );
	lg = log(s);
    srt = sqrt(-2 * lg / s);
	z1 = x * srt;
	// z2 = y * sqrt(-2 * log(s) / s);

/*z1 и z2 независимые величины удовлетворяющие стандартному нормальному распределению*/
/*переход просто к нормальному распределению осуществляется с помощью ksi=myu+sigma z ksi задаёт нормальное рсаспределние 
	/*
		0	- мат ожидание
		0.5 - дисперсия
	*/
	tmp = z1;
   	mu = 0;
	sigma = 0.5;
    ksi = mu + sigma * z1;
	 /* ksi - случайная величина распределённая по нормальному закону*/

	 fi= 2 * 3.14 * ksi;
	 delta_fi=0.01*fi;

}
  
