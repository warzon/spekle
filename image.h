#ifndef FIELD_H
#define FIELD_H

#include "boks-muller.h"
#include "canonical_fourier_transform.h"

#define AUTOCORR_BRUTE_FORCE

namespace Field {

typedef std::pair<unsigned int , unsigned int> Dimensions;

class Image {

public:
	Image(Dimensions dim, u32 slices);	
	~Image();

	void dump();
	void future();
	void computeAutoCorrelation();

	u32 timeSlices();

protected:
	void init();
	void fill();	

	void computeIntensitySampleMean();
	void computeIntensitySampleVariance();

	void bruteForceAutoCorrelation();
	void fftAutoCorrelation();

	Dimensions _dim;
	
	u32 _timeSlices;
	double **phase;
	double **disposition;
	double *intensity;
	double *autoCorrelation;	
	Complex *tension;
	double *timeLapse;	

	double _intensitySampleMean;
	double _intensitySampleVariance;
	double *intensitySampleVariance;

	Complex _tension;
	double _timeLapse;
	double _intensity;

	u32 _timeSlice;

	Fortune::BoksMuller generator;	

private:	
	std::ofstream outTension;
	std::ofstream outTimeLapse;
	std::ofstream outVars;
	std::ofstream outIntensity;
	std::ofstream outAutoCorrelation;

	void  saveVars();
};

} // namespace Field

#endif
