#ifndef FIELD_H
#define FIELD_H

#include "boks-muller.h"

namespace Field {

typedef std::pair<unsigned int , unsigned int> Dimensions;

class Image {

public:
	Image(Dimensions dim);	
	~Image();

	void dump();
	void future();
	Complex tension();

protected:
	void init();
	void fill();	

	Dimensions _dim;
	
	double **phase;
	double **disposition;
	Complex _tension;
	double _correlation;

	Fortune::BoksMuller generator;	
};

} // namespace Field

#endif
