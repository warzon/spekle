#include "boks-muller.h"

Fortune::BoksMuller::BoksMuller() {}
Fortune::BoksMuller::BoksMuller(double f, double t) : ParkMiller(f,t) {}

double Fortune::BoksMuller::normalize(double val) {
//	return mu + sigma * val;
	return 0 + 0.5 * val;
}

Fortune::Couple Fortune::BoksMuller::random() {

	double s = 0.0, x = 0.0 , y = 0.0 , z0 = 0.0 , z1  = 0.0;

	while(true) {
		x = ParkMiller::random();
		y = ParkMiller::random();

		s = x*x + y*y;

		if(s > 0 && s <= 1) break;
	}

	double tmp = sqrt( -2 * log(s) / s );  

	z0 = normalize(x * tmp);
	z1 = normalize(y * tmp);

	return Fortune::Couple(z0, z1);
}
