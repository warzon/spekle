#ifndef CANONICAL_FOURIER_TRANSFORM_H
#define CANONICAL_FOURIER_TRANSFORM_H

#include "fourier_window.h"

#define ALL_FOURIER

namespace Math {

    namespace Fourier {

    	enum Direction {
		DFT = 1,
		IDFT = -1
	};

        class Canonical : public Window
        {
	private:
		void init();
		double *_signal;
        
	public:
	    Complex *out;

        public:
            Canonical(double *signal, u32 size);
            ~Canonical();

            inline Complex get(u32 count);
	    Complex operator()(u32 count);

            void compute(Direction dir = DFT);
        };
    }
}

#endif // CANONICAL_FOURIER_TRANSFORM_H
