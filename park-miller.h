#ifndef PARKMILLER_H
#define PARKMILLER_H

#include "global.h"

#define NTAB 32
#define NWUP 8
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

/* Minimal portable random generator by Park and Miller */
/* Lewis-Goodman-Miller constants */

#define IA 16807
#define IM 2147483647

/* Scharge constants */

#define IQ 12773
#define IR 2836

/* Special mask to be explained below */

#define MASK 123456789

#define IM1 2147483563
#define IM2 2147483399
#define AM (1./IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#undef NDIV
#define NDIV (1+IMM1/NTAB)

namespace Fortune {

class ParkMiller  {

private:
    long dummy;
    double unirand0();
    double unirand1();
    double unirand2();

    double _from;
    double _to;

    void init(long seed);

public:
    ParkMiller(long seed);
    ParkMiller(double f, double t);
    ParkMiller();

    double random(double a, double b);
    double random();
};

} // namespace Fortune

#endif // PARKMILLER_H
