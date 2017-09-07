#include "image.h"

Field::Dimensions dim(0,0);
u32 TimeSlices = 0;

void init() {
	setvbuf(stdout, NULL, _IONBF, 0);
}

void assignDefaults() {
	dim = Field::Dimensions(10,10);
	TimeSlices = 1000;
}

void parseArgs(int argc, char **argv) {
	std::cout << "Configuration: " << std::endl;

	if(argc == 3) {

		TimeSlices = atoi(argv[1]);

		int tmp = atoi(argv[2]);
		dim = Field::Dimensions(tmp,tmp);

		return;
	}

	assignDefaults();
}


int main(int argc, char **argv) {

	init();
	parseArgs(argc, argv);

	std::cout << "Time Slices " << TimeSlices << std::endl;
	std::cout << "Image Dimensions {" << dim.first << "," << dim.second << "}" << std::endl;

	Field::Image image(dim, TimeSlices);
	Common::ProgressBar progress(image.timeSlices(),"Future");

	for(int i=0; i < image.timeSlices(); i++) {
		image.future();

		progress++;
	}

	image.computeAutoCorrelation();
	image.dump();

	return 0;
}
