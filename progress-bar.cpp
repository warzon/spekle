#include "progress-bar.h"

Common::ProgressBar::ProgressBar(u32 max, std::string title) 
	: _max(max) 
	, _title(title) 
	, _progress(0)
	, _realProgress(0)
	, _cols(0)
	, x(0) {

	init();

	std::cout << std::endl << title << std::endl;
	
	slash[0] = "\\";	
	slash[1] = "-";
	slash[2] = "/";
	slash[3] = "|";
}

void Common::ProgressBar::init() {
	displaySize();

	_step = _max / _cols;

	bars.resize(_cols);
	for(u32 i=0; i < _cols; i++) bars[i] = '-';
}

void Common::ProgressBar::fillBars() {
	for(u32 i=0; i < _progress; i++) {
		if(_progress < _cols)
			bars[i] = '#';
	}
}

void Common::ProgressBar::displaySize() {

#if defined TIOCGSIZE
	struct ttysize ts;
	int err = ioctl(0, TIOCGSIZE, &ts);
	if (!err) _cols = ts.ts_cols;
#elif defined TIOCGWINSZ
	struct winsize ws;
	int err = ioctl(0, TIOCGWINSZ, &ws);
	
	if (!err) _cols = ws.ws_col;
#else
#error cannot do that, bye
#endif
	if(_cols != 0)	    
		_cols -= 50;
	else
		_cols = 100;
}

Common::ProgressBar::~ProgressBar() {
	std::cout << std::endl;
}

void Common::ProgressBar::increment()
{
	fillBars();

	_progress++;

	std::cout << "\r"; // carriage return back to beginning of line
  	std::cout << "[" << bars << "] " 
			<< slash[x] << " " 
			<< ( (float)_realProgress / (float)_max ) * 100 
			<< " % "  ;
			 // print the bars and percentage
		
	x++; // increment to make the slash appear to rotate

	if(x == 4) {
		x = 0; // reset slash animation
	}
}

void Common::ProgressBar::operator++ (int val) {
	if(_realProgress % _step == 0) increment();

	_realProgress++;
}
