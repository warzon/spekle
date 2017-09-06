#ifndef FOURIER_WINDOW_H
#define FOURIER_WINDOW_H

#include "global.h"

namespace Math {

    namespace Fourier {

        class Window
        {

        protected:
		u32 _signalSize;
		double *window;

        public:
            enum Type {
                HANNING_WINDOW ,
                HEMMING_WINDOW ,
                BLACKMAN_WINDOW ,
                BLACKMAN_HARRIS_WINDOW ,
                BLACKMAN_NATALL_WINDOW ,
                FLAT_TOP_WINDOW ,
                GAUSS_WINDOW
            };

            Window(u32 size, Type wType = HANNING_WINDOW);

            ~Window();

            double HannWindow(u32 n);
            double HemmingWindow(u32 n);
            double BlackmanWindow(u32 n);
            double BlackmanHarrisWindow(u32 n);
            double BlackmanNatallWindow(u32 n);
            double FlatTopWindow(u32 n);
            double GaussWindow(double sigma, u32 n);

            double ApplyWindow(u32 count);

            void setWindowType(Type type);

            void calcWindow();

            Type type;

        };

    } // namespace Fourier

} // namespace Math

#endif // FOURIER_WINDOW_H
