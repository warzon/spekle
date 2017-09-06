#include "image.h"


Field::Image::Image(Field::Dimensions dim) 
	: _dim(dim) , generator(0,2*M_PI) , _correlation(0)
{
	init();
	fill();
}

void Field::Image::init() {
	phase = new double*[_dim.first];
	disposition = new double*[_dim.first];

	for(u32 i=0; i < _dim.first; i++)  {
		phase[i] = new double[_dim.second];
		disposition[i] = new double[_dim.second];

		for(u32 j=0; j < _dim.second; j++) {
			phase[i][j] = 0.0;
			disposition[i][j] = 0.0;
		}
	}
}

void Field::Image::fill() {
	for(u32 i=0; i < _dim.first; i++) {
		for(u32 j=0; j < _dim.second; j++) {
			phase[i][j] = generator.random().first;
		}
	}
}

Complex Field::Image::tension() {
	return _tension;
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

	u32 dim = _dim.first * _dim.second;
	
	av_disp /= dim;
	av_phase /= dim;

	_correlation = av_phase / av_disp;

	_tension = Complex(pow(x,2),pow(y,2));
}

Field::Image::~Image() {
	for(u32 i=0; i < _dim.first; i++) {
		delete[] phase[i];
		delete[] disposition[i];
	}

	delete[] disposition;
	delete[] phase;
}

void Field::Image::dump() {
	for(u32 i=0; i < _dim.first; i++) {
		for(u32 j=0; j < _dim.second; j++) {
			printf("%f ",phase[i][j]);
		}

		printf("\t");

		for(u32 j=0; j < _dim.second; j++) {
			printf("%f ", disposition[i][j]);
		}

		printf("\n");
	}

	printf("Field Tension -> %f + i %f \n", _tension.real(), _tension.imag());
	printf("Intensity -> %f \n", abs(_tension));
	printf("Correlation time -> %f \n", _correlation);

	printf("\n");
}
