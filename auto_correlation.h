#ifndef AUTO_CORRELATION_H
#define AUTO_CORRELATION_H

#include "canonical_fourier_transform.h"

namespace Math {
namespace Signal {

class Correlation {
	

public:
	Correlation(double *signalA, u32 size);

	void compute();

	double operator() (u32 k);

private:
	u32 size;
	double *_signalA;
	double *_signalB;

	double *result;
	
};

} // namespace Signal
} // namespace Math

#endif
