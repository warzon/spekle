#include "image.h"


Field::Image::Image(Field::Dimensions dim, u32 slices) 
	: 
	_dim(dim) 
	, _timeSlices(slices)
	, generator(-2*M_PI,2*M_PI)
	, _timeSlice(0)
	, _timeLapse(0)
	, _intensity(0)
	, _intensitySampleMean(0)
	, _intensitySampleVariance(0)
	, outVars("vars")
	, outTension("tension.plot")
	, outTimeLapse("timeLapse.plot")
	, outIntensity("intensity.plot")
	, outAutoCorrelation("autoCorrelation.plot")
{
	init();
	fill();
}

void Field::Image::init() {
	phase = new double*[_dim.first];
	disposition = new double*[_dim.first];
	intensity = new double[_timeSlices];
	autoCorrelation = new double[_timeSlices];
	tension = new Complex[_timeSlices];
	timeLapse = new double[_timeSlices];
	intensitySampleVariance = new double[_timeSlices];

	for(u32 i=0; i < _dim.first; i++)  {
		phase[i] = new double[_dim.second];
		disposition[i] = new double[_dim.second];
	}

	outAutoCorrelation.width(10);
	outAutoCorrelation.setf(std::ios::fixed);
}

void Field::Image::fill() {
	for(u32 i=0; i < _dim.first; i++) {
		for(u32 j=0; j < _dim.second; j++) {
			phase[i][j] = generator.random().first;
			disposition[i][j] = 0;
		}

		intensity[i] = 0;
		tension[i] = 0;
		timeLapse[i] = 0;
	}
}

u32 Field::Image::timeSlices() {
	return _timeSlices;
}

void Field::Image::future() {
	_tension = Complex(0,0);

	double x=0,y=0, av_phase = 0 , av_disp = 0;

	for(u32 i=0; i < _dim.first; i++) {
		for(u32 j=0; j < _dim.second; j++) {
			disposition[i][j] = generator.random().second * 0.01;

			av_phase += phase[i][j];
			av_disp += disposition[i][j];

			phase[i][j] += disposition[i][j];

			x += cos(phase[i][j]);
			y += sin(phase[i][j]);
		}
	}

	unsigned int dim = _dim.first * _dim.second;
	
	av_disp /= dim;
	av_phase /= dim;

	_timeLapse = av_phase / av_disp;
	_tension = Complex(pow(x,2),pow(y,2));

	// keap two values of intensity 
	// for calculation of auto correlation
	// function
	_intensity = abs(_tension);

	intensity[_timeSlice] 	= _intensity;
	tension[_timeSlice] 	= _tension;
	timeLapse[_timeSlice] 	= _timeLapse;

	_timeSlice++;
}

void Field::Image::computeIntensitySampleMean() {
	
	Common::ProgressBar progress(_timeSlices, "Intensity Sample Mean");
	
	for(u32 i=0; i < _timeSlices; i++) {
		_intensitySampleMean += intensity[i];

		progress++;
	}

	_intensitySampleMean /= _timeSlices;
}

void Field::Image::computeIntensitySampleVariance() {

	computeIntensitySampleMean();
	
	Common::ProgressBar progress(_timeSlices, "Intensity Sample Variance");

	for(u32 i=0; i < _timeSlices; i++) {
		intensitySampleVariance[i] = intensity[i] - _intensitySampleMean;

		_intensitySampleVariance += pow( intensitySampleVariance[i], 2);

		progress++;
	}

	_intensitySampleVariance /= _timeSlices;
}

void Field::Image::bruteForceAutoCorrelation() {
	computeIntensitySampleVariance();

	Common::ProgressBar progress(_timeSlices, "BruteForce Auto Correlation");

	for(u32 i=0; i < _timeSlices; i++) {
		u32 timeSlice = _timeSlices - i;

		double tmp = 0;
		double tmp1 = timeSlice *_intensitySampleVariance ;

		for(u32 t=0; t < timeSlice; t++) {
//			tmp += (intensity[t] - _intensitySampleMean) * (intensity[t+i] - _intensitySampleMean);

			tmp += intensitySampleVariance[t] * intensitySampleVariance[t+i];
		}

		autoCorrelation[i] = tmp / tmp1 ; 

		progress++;
	}
}

void Field::Image::fftAutoCorrelation() {

	Math::Fourier::Canonical fft(intensity, _timeSlices);

	fft.compute();
	Complex *tmp = new Complex[_timeSlices];

	for(u32 i=0; i < _timeSlices; i++)  {
		tmp[i] = fft(i) * conj(fft(i));

		std::cout << tmp[i] << std::endl;

		fft.out[i] = tmp[i];
	}

	fft.compute(Math::Fourier::IDFT);

	for(u32 i=0; i < _timeSlices; i++) {
		autoCorrelation[i] = fft(i).imag();
			
		std::cout << tmp[i] << "\t" << fft(i) << std::endl;
	}
	
	delete[] tmp;
}

void Field::Image::computeAutoCorrelation() {

#ifndef AUTOCORR_BRUTE_FORCE
	fftAutoCorrelation();
#else
	bruteForceAutoCorrelation();
#endif
}

Field::Image::~Image() {
	for(u32 i=0; i < _dim.first; i++) {
		delete[] phase[i];
		delete[] disposition[i];
	}

	delete[] disposition;
	delete[] phase;
	delete[] intensity;
	delete[] autoCorrelation;
	delete[] timeLapse;
	delete[] tension;
	delete[] intensitySampleVariance;
}

void Field::Image::dump() {

	std::stringstream fileName;
	u32 t = _timeSlice + 1000;

	fileName << "phaseArray" << t << ".plot";
	std::ofstream outPhaseArray(fileName.str().c_str());

	fileName.str("");
	fileName << "dispositionArray" << t << ".plot";
	std::ofstream outDispArray(fileName.str().c_str());

	fileName.str("");
	fileName << "phaseMatrix" << t << ".splot";
	std::ofstream outPhaseMatrix(fileName.str().c_str());

	fileName.str("");
	fileName << "dispositionMatrix" << t << ".splot";
	std::ofstream outDispMatrix(fileName.str().c_str());

	for(u32 i=0; i < _dim.first; i++) {
		for(u32 j=0; j < _dim.second; j++) {
			outPhaseArray << phase[i][j] << std::endl;
			outPhaseMatrix << phase[i][j] << " ";
		}
		outPhaseMatrix << std::endl;

		for(u32 j=0; j < _dim.second; j++) {
			outDispArray << disposition[i][j] << std::endl;
			outDispMatrix << disposition[i][j] << " ";
		}
		outDispMatrix << std::endl;
	}

	saveVars();
}

void Field::Image::saveVars() {

	Common::ProgressBar progress(_timeSlices, "Saving");

	for(u32 i=0; i < _timeSlices; i++) {
		outTension 	<< tension[i].real() << "\t" << tension[i].imag() << std::endl;
		outIntensity 	<< intensity[i] << std::endl;
		outTimeLapse 	<< timeLapse[i] << std::endl;	
		outAutoCorrelation << autoCorrelation[i] << std::endl;

		progress++;
	}
}
