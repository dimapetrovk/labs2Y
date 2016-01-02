#include "Gaus.h"

Gaus::Gaus() {
	cout << "Enter quantity of threads: ";
	cin >> theads;
	string tmp;
	ifstream in;
	in.open("../input.txt");
	while (!in.eof()) {
		vector<float> tmpRow;
		getline(in, tmp);//get line from file
		string tmpA;
		for (unsigned i = 0; i < tmp.size(); i++) {
			if (tmp[i] != ' ') tmpA += tmp[i];
			else {
				tmpRow.push_back(stof(tmpA)); tmpA = "";//push value into row
			}
		}
		tmpRow.push_back(stof(tmpA));
		matrix.push_back(tmpRow);//push row into matrix
	}
	in.close();
}

void Gaus::solve() {
	sort();
	triangle();
	backGaus();
}

void Gaus::print() {
	ofstream out;
	out.open("../output.txt");
	for (unsigned i = 0; i < x.size(); i++)
		out << x[i] << ' ';//output values
	out.close();
}

inline void Gaus::sort() {
	for (unsigned i = 0; i < matrix.size() - 1; i++) {
		float maxVal = matrix[i][i];//diagonal value
		unsigned maxT = i;//row with max value
		for (unsigned t = i + 1; t < matrix.size(); t++)
			if (maxVal < matrix[t][i]) {
				maxVal = matrix[t][i];
				maxT = t;
			}
		if (maxT != i) swap(matrix[i], matrix[maxT]);
	}
}

inline void Gaus::triangle() {
	for (unsigned i = 0; i < matrix.size() - 1; i++)
#pragma omp parallel for num_threads(theads)
		for (int t = i + 1; t < matrix.size(); t++) {
			for (int j = matrix.size(); j != i; j--)
				matrix[t][j] -= matrix[t][i] * matrix[i][j] / matrix[i][i];//count new values of row elements
			matrix[t][i] = 0;
		}
}

inline void Gaus::backGaus() {
	for (int t = matrix.size() - 1; t >= 0; t--) {
		float tmpX = matrix[t][matrix[t].size() - 1] / matrix[t][t];
#pragma omp parallel for num_threads(theads)
		for (int i = t - 1; i >= 0; i--)
			matrix[i][matrix[t].size() - 1] -= tmpX*matrix[i][t];//count new free values
		x.insert(x.begin(), tmpX);
	}
}
