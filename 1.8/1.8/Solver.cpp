#include "Solver.h"

Solver::Solver() {
	readFunk();
	readLimitation();
}

void Solver::solve() {
	simplex();
	while (!checkX()) {
		buildCut();
		while (notStuck()) {
			searchMinI();
			trasformation();
			if (noSolutions) {
				cout << "No solutions!\n";
				return;
			}
		}
	}
	answer();
}

inline void Solver::addDelta(string & val) {
	float tmpC = stof(val);
	if (isMax)tmpC *= -1;
	delta.push_back(tmpC);
}

inline void Solver::readFunk() {
	string tmpString;
	cout << "Enter extremum: ";
	cin >> tmpString;
	if (tmpString == "max") isMax = true;
	else isMax = false;
	cout << "Enter function L(x)=";
	cin >> tmpString;
	string tmpVal;
	for (unsigned int i = 0; i < tmpString.size(); i++) {
		if ((tmpString[i] >= '0' && tmpString[i] <= '9') || tmpString[i] == '-' || tmpString[i] == '.') tmpVal += tmpString[i];
		else if (tmpString[i] == '*') { addDelta(tmpVal); tmpVal = ""; }
	}
	getline(cin, tmpString);
	for (unsigned int i = 0; i < delta.size(); i++) {
		cout << "Enter array for " << i + 1 << " argument: ";
		getline(cin, tmpString);
		string tmpNumber;
		vector<float> tmpArray;
		for (unsigned int t = 0; t < tmpString.size(); t++)
			if (tmpString[t] != ' ') tmpNumber += tmpString[t];
			else {
				tmpArray.push_back(stof(tmpNumber));
				tmpNumber = "";
			}
			tmpArray.push_back(stof(tmpNumber));
			arrayOfX.push_back(tmpArray);
	}
}

inline void Solver::readLimitation() {
	cout << "Enter limitation:\n";
	string tmpString;
	cin >> tmpString;
	string tmpVal;
	while (tmpString != ".") {
		basis.push_back(basis.size() + delta.size());
		vector<float> tmpRow;
		for (unsigned int i = 0; i < tmpString.size(); i++) {
			if ((tmpString[i] >= '0' && tmpString[i] <= '9') || tmpString[i] == '-' || tmpString[i] == '.')  tmpVal += tmpString[i];
			else if (tmpString[i] == '*') { tmpRow.push_back(stof(tmpVal)); tmpVal = ""; }
		}
		tmpRow.push_back(stof(tmpVal));
		tmpVal = "";
		aij.push_back(tmpRow);
		cin >> tmpString;
	}
	addToFull();
}

inline void Solver::addToFull() {//add necessary zeros
	for (unsigned int i = 0; i < basis.size(); i++) {
		delta.push_back(0);
		for (unsigned int j = 0; j < basis.size(); j++) {
			if (j == i) aij[i].insert(aij[i].end() - 1, 1);
			else aij[i].insert(aij[i].end() - 1, 0);
		}
	}
	delta.push_back(0);
}

inline void Solver::simplex() {
	while (deltaVsZero()) trasformation();
}

inline void Solver::trasformation() {
	for (unsigned int t = 0; t < basis.size(); t++)
		for (unsigned int i = 0; i < delta.size(); i++)
			if (t != minT && i != minI) aij[t][i] -= aij[minT][i] * (double)aij[t][minI] / aij[minT][minI];
	for (unsigned int i = 0; i < delta.size(); i++)
		if (i != minI) delta[i] -= aij[minT][i] * (double)delta[minI] / aij[minT][minI];
	for (unsigned int i = 0; i < delta.size(); i++)
		if (i != minI) aij[minT][i] = (double)aij[minT][i] / aij[minT][minI];
	aij[minT][minI] = 1;
	delta[minI] = 0;
	for (unsigned int t = 0; t < basis.size(); t++)
		if (t != minT) aij[t][minI] = 0;

	basis[minT] = minI;
}

inline bool Solver::deltaVsZero() {
	bool isTrue = false;
	unsigned mint;
	float MIN = 0;
	for (unsigned int i = 0; i < delta.size() - 1; i++)
		if (delta[i] < 0) {
			isTrue = true;
			float min = 0;
			for (unsigned int t = 0; t < basis.size(); t++) {
				if (aij[t][i]>0) {
					float tmp = (float)aij[t][aij[t].size() - 1] / aij[t][i];
					if (tmp < min || !min) {
						min = tmp;
						mint = t;
					}
				}
			}
			if (aij[mint][i]>0 && MIN > min*delta[i] || !MIN) {
				MIN = min*delta[i]; minI = i; minT = mint;
			}
		}
	return isTrue;
}

inline bool Solver::checkX() {
	for (unsigned int i = 0; i < arrayOfX.size(); i++) {
		for (unsigned int t = 0; t < basis.size(); t++) {
			if (basis[t] == i && !checkInArrayOfX(aij[t][aij[t].size() - 1], i)) {
				strForCut = t; return false;
			}
		}
	}
	return true;
}

inline bool Solver::checkInArrayOfX(float val, unsigned int arg) {
	unsigned i = 0;
	while (i<arrayOfX[arg].size() && val > arrayOfX[arg][i])i++;
	if (i<arrayOfX[arg].size() && abs(val - arrayOfX[arg][i])<0.0001)return true;
	if (i) XijForCut = arrayOfX[arg][i - 1];
	else XijForCut = 0;
	if (i<arrayOfX[arg].size())XijForCutPlus1 = arrayOfX[arg][i];
	else XijForCutPlus1 = arrayOfX[arg][arrayOfX[arg].size() - 1];
	return false;
}

inline void Solver::answer() {
	cout << "Solution: X(";
	for (unsigned int i = 0; i < arrayOfX.size(); i++) {
		bool out = false;
		for (unsigned int t = 0; t < basis.size(); t++) {
			if (basis[t] == i) {
				cout << aij[t][aij[t].size() - 1] << ' ';
				out = true;
				break;
			}
		}
		if (!out) cout << 0 << ' ';
	}
	cout << ")\nAnswer: " << delta[delta.size() - 1] << endl;
}

inline void Solver::buildCut() {
	vector<float> z;
	float x0;
	x0 = XijForCut - aij[strForCut][delta.size() - 1];
	z.push_back(x0);
	for (unsigned i = 0; i < delta.size() - 1; i++) {
		float xi;
		if (find(basis.begin(), basis.end(), i) == basis.end()) {
			xi = -aij[strForCut][i];
			if (aij[strForCut][i] < 0) xi *= x0 / (XijForCutPlus1 - aij[strForCut][delta.size() - 1]);
		}
		else xi = 0;
		z.insert(z.end() - 1, xi);
	}
	z.insert(z.end() - 1, 1);
	for (unsigned i = 0; i < aij.size(); i++)
		aij[i].insert(aij[i].end() - 1, 0);
	delta.insert(delta.end() - 1, 0);
	aij.push_back(z);
	basis.push_back(delta.size() - 2);
}

inline bool Solver::notStuck() {
	float min = 0;
	bool resume = false;
	for (unsigned int t = 0; t < basis.size(); t++)
		if (aij[t][aij[t].size() - 1] < 0) {
			noSolutions = true;
			for (unsigned i = 0; i < delta.size() - 1; i++) if (aij[t][i] < 0) noSolutions = false;
			if (min > aij[t][aij[t].size() - 1]) {
				min = aij[t][aij[t].size() - 1];
				minT = t;
				resume = true;
			}
		}
	return resume;
}

inline void Solver::searchMinI() {
	float min = 0;
	for (unsigned i = 0; i < delta.size() - 1; i++) if (find(basis.begin(), basis.end(), i) == basis.end() && (!min || min > -(float)delta[i] / aij[minT][i])) {
		min = -(float)delta[i] / aij[minT][i];
		minI = i;
	}
}
