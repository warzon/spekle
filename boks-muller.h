#ifndef BOKS_MULLER_H
#define BOKS_MULLER_H

#include "park-miller.h"

namespace Fortune {

typedef std::pair<double, double> Couple;

class BoksMuller : public ParkMiller {

private:
	static const double sigma = 0.5;
	static const double mu = 0;

	double normalize(double val);

public:
	BoksMuller();
	BoksMuller(double f, double t);

	Couple random();
};

} // namespace Fortune

#endif
