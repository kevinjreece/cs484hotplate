#include <iostream>
#include <iomanip>

#include "Hotplate.h"
#include "time.h"

#define LENGTH 4096

using namespace std;

const char filename[] = "test.csv";

int main(int argc, char* argv[]) {
	double time_b = getTime();

	Hotplate plate = Hotplate(LENGTH);
	// cout << plate.toString();
	plate.createSteadyState();
	// cout << plate.toString() << "\n";
	plate.printToFile(filename);

	double time_e = getTime();
	printf("Time: %lf seconds\n", time_e - time_b);
	return 0;
}
















