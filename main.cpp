#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

typedef long double TNum;

const TNum STEP_ORIG = .01;

class Solution {
public:
	TNum X;
	TNum Y;
};

TNum f1(TNum x) {
	return log(x);
}
TNum k1(TNum x, TNum s) {
	return (4*s - 5*x) / (s * s);
}


TNum df1(TNum x) {
	return 1./x;
}
TNum dk1(TNum x, TNum s) {
	//return 2 * x * exp(x*x - s*s);
	return -5. / (s * s);
}

TNum f1_new(TNum x) {
	return df1(x) / k1(x,x);
}
TNum k1_new(TNum x, TNum s) {
	return dk1(x, s) / k1(x, x);
}

TNum f2(TNum x) {
	return exp(x * x);
}
TNum k2(TNum x, TNum s) {
	return exp(x*x - s*s);
}

TNum yCorrect(TNum x, size_t mode) {
	if (mode == 2) {
		return exp(x*x + x);
	}
	return x*x * (log(x) + 1);
}

void Volterra_I_Solve(TNum a, TNum b, size_t n, TNum &h, vector <Solution> &res) {
	h = (b - a) / (n - 1);

	res.resize(n);
	TNum x_tmp = a;
	for (size_t i = 0; i < res.size(); i++) {
		res[i].X = x_tmp;
		x_tmp += h;
	}

	res[0].Y = f1_new(a);

	for (size_t i = 1; i < n; i++) {
		TNum s = 0;
		if (i > 0) {
			for (size_t j = 0; j < i - 1; j++) {
				s += k1_new(res[i].X, res[j].X) * res[j].Y;
			}
		}
		res[i].Y = (1 / (1 - h/2 * k1_new(res[i].X, res[i].X))) * (f1_new(res[i].X) + h/2 * k1_new(res[i].X, res[1].X) * res[1].Y + h * s);
	}
}

void Volterra_II_Solve(TNum a, TNum b, size_t n, TNum &h, vector <Solution> &res) {
	h = (b - a) / (n - 1);

	res.resize(n);
	TNum x_tmp = a;
	for (size_t i = 0; i < res.size(); i++) {
		res[i].X = x_tmp;
		x_tmp += h;
	}

	res[0].Y = f2(a);

	for (size_t i = 1; i < n; i++) {
		TNum s = 0;
		if (i > 0) {
			for (size_t j = 0; j < i - 1; j++) {
				s += k2(res[i].X, res[j].X) * res[j].Y;
			}
		}
		res[i].Y = (1 / (1 - h/2 * k2(res[i].X, res[i].X))) * (f2(res[i].X) + h/2 * k2(res[i].X, res[1].X) * res[1].Y + h * s);
	}
}

int main(int argc, char* argv[]) {
	if (argc < 5) {
		cout << "# ERROR: Required data is not set" << endl;
		return 1;
	}
	vector <Solution> res;
	size_t mode = (size_t) atoi(argv[1]);
	TNum a = (TNum) atof(argv[2]);
	TNum b = (TNum) atof(argv[3]);
	size_t n = (size_t) atoi(argv[4]);
	TNum h;

	if (mode == 1) {
		Volterra_I_Solve(a, b, n, h, res);
	} else if (mode == 2) {
		Volterra_II_Solve(a, b, n, h, res);
	} else {
		cout << "# ERROR: Unknown mode" << endl;
		return 2;
	}

	ofstream outNumeral("plot-numeral.dat");
	ofstream outOriginal("plot-original.dat");

	for (size_t i = 0; i < res.size(); i++) {
		outNumeral << res[i].X << " " << res[i].Y << endl;
	}
	outNumeral.close();

	for (TNum curr = a; curr <= b; curr += STEP_ORIG) {
		outOriginal << curr << " " << yCorrect(curr, mode) << endl;
	}

	outOriginal.close();

	return 0;
}
