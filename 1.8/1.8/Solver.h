#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solver {
	vector<float> delta;
	vector<unsigned> basis;
	vector<vector<float>> aij;//matrix
	vector<vector<float>> arrayOfX;//array of allowable values
	unsigned minI, minT;//min elements
	bool isMax;//kind of extremum
	bool noSolutions;
	unsigned strForCut;
	float XijForCut;
	float XijForCutPlus1;
public: Solver();
		void solve();
private: void addDelta(string &val);//add delta func

		 void readFunk();//read func from console
		 void readLimitation();//read limitations from console
		 void addToFull();//make full matrix

		 void simplex();//simplex method

		 void trasformation();//transformation step

		 bool deltaVsZero();//compare all deltas with zero
		 bool checkX();
		 bool checkInArrayOfX(float val, unsigned int arg);
		 void answer(); //show solution

		 void buildCut();

		 bool notStuck();//posibility for continuation

		 void searchMinI(); //search elem with min value
};