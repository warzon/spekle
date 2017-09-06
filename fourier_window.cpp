#include "fourier_window.h"

namespace Math {
namespace Fourier {

Window::Window(u32 size, Window::Type type) : 
	window(NULL) , _signalSize(size)
{
    setWindowType(type);
}

Window::~Window() {
    if(window)
        delete[] window;
}

void Window::calcWindow() {
    window = new double[_signalSize];

    for(u32 i=0; i < _signalSize; i++) window[i] = ApplyWindow(i);
}

double Window::HannWindow(u32 n) {
    return 0.5 * ( 1 - cos( ( 2 * M_PI * n ) / ( _signalSize ) ) );
//    return 0.5 * ( 1 - cos( ( 2 * M_PI * n ) / ( _signalSize - 1) ) );
//    return pow(sin( (M_PI * n) / ( _signalSize - 1) ),2);
}

/* sigma - 0.1 ; 0.3 ; 0.5 */
double Window::GaussWindow(double sigma, u32 n) {
    double A = ( _signalSize - 1 ) / _signalSize;
    return exp ( -0.5 * ( pow((_signalSize - A) / ( sigma * A  ), 2)  )  );
}

double Window::HemmingWindow(u32 n) {
    return 0.54 - 0.46 * cos( ( 2 * M_PI * n ) / (_signalSize)  );
//    return 0.54 - 0.46 * cos( ( 2 * M_PI * n ) / (_signalSize - 1)  );
}

double Window::BlackmanWindow(u32 n) {
    const double a_0 = 0.42;
    const double a_1 = 0.5;
    const double a_2 = 0.08;

    const double tmp = M_PI * n / (_signalSize );
//    const double tmp = M_PI * n / (_signalSize - 1);

    return  a_0 -
            a_1 * cos(2 * tmp) +
            a_2 * cos(4 * tmp);
}

double Window::BlackmanHarrisWindow(u32 n) {
    const double a_0 = 0.35875;
    const double a_1 = 0.48829;
    const double a_2 = 0.14128;
    const double a_3 = 0.01168;

    const double tmp = M_PI * n / (_signalSize );
//    const double tmp = M_PI * n / (_signalSize - 1);

    return  a_0 -
            a_1 * cos(2 * tmp) +
            a_2 * cos(4 * tmp) +
            a_3 * cos(6 * tmp);
}

double Window::BlackmanNatallWindow(u32 n) {
    const double a_0 = 0.3635819;
    const double a_1 = 0.4891775;
    const double a_2 = 0.1365995;
    const double a_3 = 0.0106411;

    const double tmp = M_PI * n / (_signalSize );
//    const double tmp = M_PI * n / (_signalSize - 1);

    return  a_0 -
            a_1 * cos(2 * tmp) +
            a_2 * cos(4 * tmp) -
            a_3 * cos(6 * tmp);
}

double Window::FlatTopWindow(u32 n) {
    const double a_0 = 1.0;
    const double a_1 = 1.93;
    const double a_2 = 1.29;
    const double a_3 = 0.388;
    const double a_4 = 0.032;

    const double tmp = M_PI * n / (_signalSize);
//    const double tmp = M_PI * n / (_signalSize - 1);

    return  a_0 -
            a_1 * cos(2 * tmp) +
            a_2 * cos(4 * tmp) -
            a_3 * cos(6 * tmp) +
            a_4 * cos(8 * tmp);
}

double Window::ApplyWindow(u32 n) {
    switch(type) {
    case HEMMING_WINDOW:            return HemmingWindow(n);
    case BLACKMAN_WINDOW:           return BlackmanWindow(n);
    case BLACKMAN_NATALL_WINDOW:    return BlackmanNatallWindow(n);
    case BLACKMAN_HARRIS_WINDOW:    return BlackmanHarrisWindow(n);
    case FLAT_TOP_WINDOW:           return FlatTopWindow(n);
    default: case HANNING_WINDOW:      return HannWindow(n);
    }
}

void Window::setWindowType(Window::Type t) {
    type = t;
}

} // namespace Fourier

} // namespace Math
