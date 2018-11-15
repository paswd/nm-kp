#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef long double TNum;

bool isNum(string str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return true;
}

size_t strToNum(string str) {
	istringstream ss(str);
	size_t res;
	ss >> res;
	return res;
}

const TNum STEP_ORIG = .01;

class Solution {
public:
	TNum X;
	TNum Y;
};

TNum f(TNum x) {
	return exp(x * x);
}
TNum k(TNum x, TNum s) {
	return exp(x*x - s*s);
}

TNum yCorrect(TNum x) {
	return exp(x*x + x);
}

void Volterra_II_Solve(TNum a, TNum b, size_t n, TNum &h, vector <Solution> &res) {
	h = (b - a) / (n - 1);

	res.resize(n);
	TNum x_tmp = a;
	for (size_t i = 0; i < res.size(); i++) {
		res[i].X = x_tmp;
		x_tmp += h;
	}

	res[0].Y = f(a);

	for (size_t i = 1; i < n; i++) {
		TNum s = 0;
		if (i > 0) {
			for (size_t j = 0; j < i - 1; j++) {
				s += k(res[i].X, res[j].X) * res[j].Y;
			}
		}
		res[i].Y = (1 / (1 - h/2 * k(res[i].X, res[i].X))) * (f(res[i].X) + h/2 * k(res[i].X, res[1].X) * res[1].Y + h * s);
	}

}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		cout << "# ERROR: Required data is not set" << endl;
		return 1;
	}
	bool isPlotEps = false;
	vector <Solution> res;
	TNum a = (TNum) atof(argv[1]);
	TNum b = (TNum) atof(argv[2]);
	size_t n = 1;
	string argv3(argv[3]);
	if (argv3 == "eps") {
		isPlotEps = true;
	} else if (isNum(argv3)) {
		n = strToNum(argv3);
	}
	TNum h;

	ofstream outNumeral;
	ofstream outOriginal;
	ofstream outEps;

	size_t start;
	size_t end;

	if (isPlotEps) {
		outEps.open("plot-eps.dat");
		if (argc < 5) {
			cout << "# ERROR: Required data is not set" << endl;
			return 1;
		}
		start = 2;
		end = (size_t) atoi(argv[4]);
	} else {
		outNumeral.open("plot-numeral.dat");
		outOriginal.open("plot-original.dat");
		start = n;
		end = n;
	}

	for (size_t nCurr = start; nCurr <= end; nCurr++) {
		Volterra_II_Solve(a, b, nCurr, h, res);

		double maxDiff = 0.;
		for (size_t i = 0; i < res.size(); i++) {
			if (!isPlotEps) {
				outNumeral << res[i].X << " " << res[i].Y << endl;
			}
			double currDiff = abs(res[i].Y - yCorrect(res[i].X));
			if (currDiff > maxDiff) {
				maxDiff = currDiff;
			}
		}
		if (isPlotEps) {
			outEps << nCurr << " " << maxDiff << endl;
		} else {
			for (TNum curr = a; curr <= b; curr += STEP_ORIG) {
				outOriginal << curr << " " << yCorrect(curr) << endl;
			}

		
			cout << "Шаг: " << h << endl;
			cout << "Погрешность: " << maxDiff << endl;
		}
	}
	if (isPlotEps) {
		outEps.close();
	} else {
		outNumeral.close();
		outOriginal.close();
	}

	return 0;
}
