#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <sys/ioctl.h>
#include "global.h"

namespace Common {

class ProgressBar {

private:
	std::string _title;
	u32 _max;
	int _step;
	std::string bars;
	std::string slash[4];
	int x;
	int _cols;

	u32 _progress;
	u32 _realProgress;

	void displaySize();
	void fillBars();
	void init();

public:
	ProgressBar(u32 max, std::string title);
	~ProgressBar();	

	void increment();

	void operator++(int val);
};

} // namespace Common

#endif
