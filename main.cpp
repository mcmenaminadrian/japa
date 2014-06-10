#include <iostream>
#include "page.hpp"
#include "expat.h"

use namespace std;


void usage()
{
	cout << "japa - just another paging analyser\n";
	cout << "Basic usage:\n";
	cout << "\tjapa inputfile\n";
	cout << "Options:\n";
	cout << "\t-i\t\tIntensity (default)\n";
	cout << "\t-ni\t\tDo not measure intensity\n";
	return;
}

int main(int argc, char *argv[])
{
	bool intensity = true; //default use case
	bool breadth = false;
	
	if (argc < 2) {
		usage();
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if ((strcmp(argv[i], "-i") == 0) {
			intensity = true;
		}

		if (strcmp(argv[i], "-ni") == 0) {
			intensity = false;
		}
