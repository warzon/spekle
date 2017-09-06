#include "canonical_fourier_transform.h"

namespace Math {
namespace Fourier {

Canonical::Canonical(double *signal, u32 size) 
	: Window(size) 
	, _signal(signal) { 
	init();
}

Canonical::~Canonical() {
	delete[] out;
}

void Canonical::init() {
	out = new Complex[_signalSize];
	    
	for(u32 i = 0;i < _signalSize; i++ ) {
        	out[i] = Complex(_signal[i],0);
	}
}

Complex Canonical::get(u32 count) {
    return out[count];
}

Complex Canonical::operator() (u32 count) {
	return get(count);
}

void Canonical::compute(Direction dir) {
    Complex  carg,ctemp,cw,sw;
    u32 j,l,m,i,istep;

    j = 0;

    switch(dir) {
    case DFT: sw = 1.; break;
    case IDFT: sw = 1./_signalSize; break;
    }

    for(i = 0;i < _signalSize;i++) {
        if( i <= j ) {
            ctemp = out[j] * sw;
            out[j] = out[i] * sw;
            out[i] = ctemp;
        }

        m = _signalSize / 2;

        m20:
        if( j >= m ) {
            j = j - m;
            m = m / 2;
            if( m >= 1 ) goto m20;
        }

        j = j + m;
    }

    l = 1;

    do {
        istep = 2*l;
        for (m = 0; m < l; m++) {
            carg = Complex(0, 1. * M_PI * dir * m / l);
            cw   = exp(carg);
            j = 1;

            for ( i = m; i < _signalSize; ) {
                ctemp = out[i + l] * cw;

                out[i+l] = out[i] - ctemp;
                out[i]   = out[i] + ctemp;
                i += istep;
            }
        }

        l = istep;
    } while(l < _signalSize);
}

} // namespace Fourier

} // namespace Math
