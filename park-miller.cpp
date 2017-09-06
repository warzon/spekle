#include "park-miller.h"

Fortune::ParkMiller::ParkMiller(long seed) {
    	init(seed);
}

Fortune::ParkMiller::ParkMiller(double f , double t) : _to(t), _from(f) {
	init(time(NULL));
}

Fortune::ParkMiller::ParkMiller() {
	init(time(NULL));
}

void Fortune::ParkMiller::init(long seed) {
	this->dummy = seed;
}

double Fortune::ParkMiller::unirand0() {
    long k;
    double ans;

    dummy ^= MASK;

    /* avoid dummy==0 */

    k = dummy/IQ;

    if((dummy = IA*(dummy - k*IQ) - IR*k) < 0)
            dummy += IM;

    ans = AM*dummy;
    dummy ^= MASK;
    /* restore unmasked dummy */

    return(ans);
}

double Fortune::ParkMiller::unirand1() {
    int j;
    long k;
    static long iy=0,iv[NTAB];

    double temp;

    /* initialize */
    if(dummy <= 0 || !iy)
    {
            /* avoid negative or zero seed */
            if(dummy < 0) dummy =- dummy;
            else if(dummy == 0) dummy = 1;

            /* after NWUP warmups, initialize shuffle table */
            for(j=NTAB+NWUP-1;j>=0;j--)
            {
                    k=dummy/IQ;

                    if((dummy=IA*(dummy-k*IQ)-IR*k)<0)
                            dummy+=IM;

                    if(j<NTAB)
                            iv[j]=dummy;
            }

            /* first specimen from the table */
            iy=iv[0];
    }

    /* regular work: generate new number */
    k = dummy/IQ;

    if((dummy=IA*(dummy-k*IQ)-IR*k)<0)
            dummy+=IM;

    /* shuffle output */
    iy=iv[j=iy/NDIV];iv[j]=dummy;

    /* return */
    if((temp = AM*iy) > RNMX)
            return(RNMX);
    else
            return(temp);
}

double Fortune::ParkMiller::unirand2() {
    int j;
    long k;
    static long dummy2=123456789;
    static long iy=0;
    static long iv[NTAB];
    double temp;

    /* initialize the random sequence (first set of coefficients, the
       routine close to that in the function above */
    if(dummy<=0 || !iy)
    {
            /* avoid negative or zero seed */
            if(dummy<0) dummy=-dummy;
            else if(dummy==0) dummy=1;
            dummy2=dummy;

            /* after NWUP warmups, initialize shuffle table */
            for(j=NTAB+NWUP-1;j>=0;j--)
            {
                    k=dummy/IQ1;
                    if((dummy=IA1*(dummy-k*IQ1)-IR1*k)<0) dummy+=IM1;

                    if(j<NTAB) iv[j]=dummy;
            }

            /* first specimen from the table */
            iy=iv[0];
    }

    /* regular work: generate 2 sequences. */
    k=dummy/IQ1;
    if((dummy=IA1*(dummy-k*IQ1)-IR1*k)<0) dummy+=IM1;

    k=dummy2/IQ2;
    if((dummy2=IA2*(dummy2-k*IQ2)-IR2*k)<0) dummy2+=IM2;

    /* shuffle output combining 2 sequences */
    iy=iv[j=iy/NDIV]-dummy2;iv[j]=dummy;
    if(iy<1) iy+=IMM1;

    /* return the result, as in the previous function */
    if((temp=AM*iy)>RNMX) return(RNMX);
    else return(temp);
}

double Fortune::ParkMiller::random(double a, double b) {
    return (b - a)*this->unirand2() + a;
}

double Fortune::ParkMiller::random() {
	return (_to - _from) * this->unirand2() + _from;
}
