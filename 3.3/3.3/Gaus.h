#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <omp.h>
using namespace std;

class Gaus {
	vector<vector<float>> matrix;//matrix
	vector<float> x;//values
	int theads;//numb of threads

public: Gaus();//constructor

		void solve();//solve system
		void print();//show result

private:void sort();//sort equations by diagonals values

		void triangle();//make triangle view

		void backGaus();//back algorithm
};