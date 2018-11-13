#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long double TNum;

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
	vector <Solution> res;
	//TNum a, b, h;
	//size_t n;
	//cin >> a >> b >> n;
	TNum a = (TNum) atof(argv[1]);
	TNum b = (TNum) atof(argv[2]);
	size_t n = (size_t) atoi(argv[3]);
	TNum h;

	Volterra_II_Solve(a, b, n, h, res);

	for (size_t i = 0; i < res.size(); i++) {
		cout << res[i].X << " " << res[i].Y << " " << yCorrect(res[i].X) << endl;
	}

	return 0;
}
