#pragma once
#include <iostream>
using namespace std;

class elementOfVector {
public: float val;
		string name;
};

class elementOfVectorA:public elementOfVector {
public: bool isBasis=false;
};