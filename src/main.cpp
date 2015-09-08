#include <iostream>
#include <iomanip>
#include <sys/time.h>

#include "Hotplate.h"

#define LENGTH 5

using namespace std;

/* Return the current time in seconds, using a double precision number. */
float getTime() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
}

int main(int argc, char* argv[]) {
	float time_b = getTime();
	cout << setprecision(15) << time_b << "\n";

	Hotplate plate = Hotplate(LENGTH);
	// cout << plate.toString();
	plate.createSteadyState();
	cout << plate.toString();
	plate.printToFile("test.csv");

	float time_e = getTime();
	cout << time_e << "\n";
}
















