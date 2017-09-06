#include "image.h"

int main(int argc, char **argv) {

	freopen("data.txt", "w+", stdout);

	Field::Image image(Field::Dimensions(10,10));
	
	for(int i=0; i < 4; i++) {
		image.dump();
		image.future();
	}

	return 0;
}
