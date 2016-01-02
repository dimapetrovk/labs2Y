#include "Gaus.h"
#include <Windows.h>
#include <iostream>

using uint64 = unsigned long long int;

void main() {
	Gaus myGaus;//create matrix
	
	//recod time
	uint64 frequencyU64 = 0;
	QueryPerformanceFrequency(PLARGE_INTEGER(&frequencyU64));

	uint64 recordStartU64 = 0;
	QueryPerformanceCounter(PLARGE_INTEGER(&recordStartU64));

	myGaus.solve();

	uint64 recordStopU64 = 0;
	QueryPerformanceCounter(PLARGE_INTEGER(&recordStopU64));

	myGaus.print();//show result
	cout<<float(recordStopU64 - recordStartU64) / float(frequencyU64);//show time
	system("pause");
}