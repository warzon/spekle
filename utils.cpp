#include "utils.h"

std::string ltoa(long value) {

	char *tmp = new char[10];

	sprintf(tmp,"%ld",value);

	std::string res(tmp);

	delete tmp;

	return res;
}

std::string itoa(int value) {

	char *tmp = new char[10];

	sprintf(tmp,"%d",value);

	std::string res(tmp);

	delete tmp;

	return res;
}

std::string ftoa(double value) {
	char *tmp = new char[10];

	sprintf(tmp, "%f", value);

	std::string res(tmp);

	delete tmp;

	return res;
}
