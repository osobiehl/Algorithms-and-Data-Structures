#include <iostream>
#include "WindGauge.h"

using namespace std;
int main() {
	//15, 16, 12, 15, and 15
	WindGauge test;
	test.currentWindSpeed(15);
	test.currentWindSpeed(16);
	test.currentWindSpeed(12);
	test.currentWindSpeed(15);
	test.currentWindSpeed(15);
	test.dump();
	int measurements[] = {16, 17, 16, 16, 20, 17, 16, 15, 16, 20};
	for (int thing : measurements){
		test.currentWindSpeed(thing);
	}
	test.dump();



}
